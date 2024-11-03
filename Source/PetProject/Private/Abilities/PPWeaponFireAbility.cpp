// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/PPWeaponFireAbility.h"
#include "ItemData/PPItemData.h"
#include "PPInventoryComponent.h"

FTransform UPPWeaponFireAbility::GetTargetingTransform(APawn* SourcePawn)
{
	AController* Controller = SourcePawn->Controller;

	double FocalDistance = 1024.0f;
	
	FVector FocalLoc;
	FVector CamLoc;
	FRotator CamRot;

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (IsValid(PlayerController))
	{
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);
	}
	else
	{
		//for bots
	}

	FVector AimDir = CamRot.Vector().GetSafeNormal();
	FocalLoc = CamLoc + (AimDir * FocalDistance);

	if (IsValid(PlayerController))
	{
		FVector WeaponLoc = SourcePawn->GetActorLocation();
		CamLoc = FocalLoc + (((WeaponLoc - FocalLoc) | AimDir) * AimDir);
		FocalLoc = CamLoc + (AimDir * FocalDistance);
	}

	return FTransform(CamRot, CamLoc);
}

void UPPWeaponFireAbility::StartWeaponTargeting()
{
	TArray<FHitResult> HitResults;
	//HitResults.Reserve(10);

	PerformLocalTargeting(HitResults);

	FGameplayAbilityTargetDataHandle TargetData;

	for (FHitResult& Hit : HitResults)
	{
		FGameplayAbilityTargetData_SingleTargetHit* NewTargetData = new FGameplayAbilityTargetData_SingleTargetHit(Hit);
		TargetData.Add(NewTargetData);
	}

	OnRangedWeaponTargetDataReady(TargetData);
}

void UPPWeaponFireAbility::PerformLocalTargeting(TArray<FHitResult>& OutHits)
{
	APawn* AvatarPawn = Cast<APawn>(GetAvatarActorFromActorInfo());

	if (IsValid(AvatarPawn))
	{
		FTransform Transform = GetTargetingTransform(AvatarPawn);

		FVector AimDir = Transform.GetUnitAxis(EAxis::X);
		FVector StartTrace = Transform.GetTranslation();
		FVector EndAim = StartTrace + AimDir * 10000;

		TraceBulletsInCartridge(StartTrace, EndAim, OutHits);
	}
}

void UPPWeaponFireAbility::TraceBulletsInCartridge(FVector& StartTrace, FVector& EndAim, TArray<FHitResult>& OutHits)
{
	UPPItem* ItemData = GetWeaponData();

	if (!IsValid(ItemData))
	{
		return;
	}

	FHitResult Hit; 

	if (ItemData->BulletsInCartridge > 1)
	{
		TraceBulletsSpread(StartTrace, EndAim, ItemData->BulletsInCartridge, OutHits);
	}
	else
	{
		GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndAim, ECollisionChannel::ECC_Camera, FCollisionQueryParams(FName(), true, GetAvatarActorFromActorInfo()));
		DrawDebugLine(GetWorld(), StartTrace, EndAim, FColor::Yellow, false, 2, 0, 2);
		OutHits.Add(Hit);
	}
}

UPPItem* UPPWeaponFireAbility::GetWeaponData() const
{
	APawn* Pawn = Cast<APawn>(GetAvatarActorFromActorInfo());

	if (!IsValid(Pawn))
	{
		return nullptr;
	}

	UPPInventoryComponent* PlayerInventory = UPPInventoryComponent::GetInventoryComponentFromActor(Pawn->GetController());

	if (IsValid(PlayerInventory))
	{
		//return PlayerInventory->GetActiveItem();
	}

	return nullptr;
}

void UPPWeaponFireAbility::TraceBulletsSpread(FVector& StartTrace, FVector& EndAim, int32 Bullets, TArray<FHitResult>& OutHits)
{
	for (int32 i = 0; i < Bullets; ++i)
	{
		EndAim.X += FMath::FRandRange(-300.0, 300.0);
		EndAim.Y += FMath::FRandRange(-300.0, 300.0);
		EndAim.Z += FMath::FRandRange(-300.0, 300.0);

		FHitResult Hit;

		GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndAim, ECollisionChannel::ECC_Camera, FCollisionQueryParams(FName(), true, GetAvatarActorFromActorInfo()));
		DrawDebugLine(GetWorld(), StartTrace, EndAim, FColor::Yellow, false, 2, 0, 2);
		OutHits.Add(Hit);
	}
}

