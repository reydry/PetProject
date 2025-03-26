// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/PPWeaponSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"

UPPWeaponSet::UPPWeaponSet()
{
}

void UPPWeaponSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetPrimaryAmmoAttribute())
	{
		SetPrimaryAmmo(FMath::Max(GetPrimaryAmmo(), 0.0f));

		if (FMath::IsNearlyZero(GetPrimaryAmmo()))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningActor(), FGameplayTag::RequestGameplayTag("Ability.Reload"), FGameplayEventData());
		}
	}

	if (Data.EvaluatedData.Attribute == GetSecondaryAmmoAttribute())
	{
		SetSecondaryAmmo(FMath::Max(GetSecondaryAmmo(), 0.0f));
	}
}
