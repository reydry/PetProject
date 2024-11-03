// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PPWeaponFireAbility.generated.h"

class UPPItem;

UCLASS()
class PETPROJECT_API UPPWeaponFireAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	FTransform GetTargetingTransform(APawn* SourcePawn);

	UFUNCTION(BlueprintCallable)
	void StartWeaponTargeting();

	void PerformLocalTargeting(TArray<FHitResult>& OutHits);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRangedWeaponTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);

	void TraceBulletsInCartridge(FVector& StartTrace, FVector& EndAim, TArray<FHitResult>& OutHits);

	UPPItem* GetWeaponData() const;

	void TraceBulletsSpread(FVector& StartTrace, FVector& EndAim, int32 Bullets, TArray<FHitResult>& OutHits);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GameplayEffectToApply;

private:
	FDelegateHandle OnTargetDataReadyCallbackDelegateHandle;
};
