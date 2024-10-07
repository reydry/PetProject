// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/PPCharacterSet.h"
#include "GameplayEffectExtension.h"

UPPCharacterSet::UPPCharacterSet()
{

}

void UPPCharacterSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (FMath::IsNearlyZero(GetHealth()))
		{
			OnDeathDelegate.Broadcast();
		}
	}

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
}
