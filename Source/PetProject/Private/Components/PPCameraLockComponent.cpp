// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PPCameraLockComponent.h"
#include "Characters/PPCharacter.h"
#include "Attributes/PPCharacterSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPPCameraLockComponent::UPPCameraLockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UPPCameraLockComponent* UPPCameraLockComponent::GetCameraLockComponentFromActor(const AActor* InActor)
{
	if (IsValid(InActor))
	{
		return InActor->FindComponentByClass<UPPCameraLockComponent>();
	}

	return nullptr;
}

void UPPCameraLockComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitComponents();
}

void UPPCameraLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateCameraRotation();	
	CheckDistanceToTarget();
}

void UPPCameraLockComponent::SetTarget(AActor* InTarget)
{
	UnSubscribeFromDelegates();

	Target = Cast<APPCharacter>(InTarget);

	SubscribeToDelegates();
}

void UPPCameraLockComponent::SetLockOnTarget(bool InLockOnTarget)
{
	bLockOnTarget = InLockOnTarget;

	SetComponentTickEnabled(InLockOnTarget);
}

AActor* UPPCameraLockComponent::GetTarget() const
{
	return Target;
}

void UPPCameraLockComponent::CheckDistanceToTarget()
{
	if (!IsValid(Target) || !IsValid(Owner))
	{
		return;
	}

	double Distance = FVector::Distance(Target->GetActorLocation(), Owner->GetActorLocation());

	if (Distance > DistanceThreshold)
	{
		TargetLost(Target);
	}
}

void UPPCameraLockComponent::TargetLost(AActor* DestroyedActor)
{
	UnSubscribeFromDelegates();

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, FGameplayTag::RequestGameplayTag(TEXT("GameplayEvent.TargetLost")), FGameplayEventData());
}

void UPPCameraLockComponent::SubscribeToDelegates()
{
	if (!IsValid(Target))
	{
		return;
	}

	Target->OnDestroyed.AddUniqueDynamic(this, &ThisClass::TargetLost);
}

void UPPCameraLockComponent::UnSubscribeFromDelegates()
{
	if (!IsValid(Target))
	{
		return;
	}

	Target->OnDestroyed.RemoveDynamic(this, &ThisClass::TargetLost);
}

void UPPCameraLockComponent::UpdateCameraRotation()
{
	if ((!IsValid(PlayerController) || !IsValid(Target) || !IsValid(Owner)) && !bLockOnTarget)
	{
		return;
	}

	FVector PlayerLocation = Owner->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);

	PlayerController->SetControlRotation(TargetRotation);
}

void UPPCameraLockComponent::InitComponents()
{
	APPCharacter* PlayerOwner = GetOwner<APPCharacter>();

	if (IsValid(PlayerOwner))
	{
		PlayerController = PlayerOwner->GetController<APlayerController>();
		Owner = PlayerOwner;
	}

	SetComponentTickEnabled(false);
}

