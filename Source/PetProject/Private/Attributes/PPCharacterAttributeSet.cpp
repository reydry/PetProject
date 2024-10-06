// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/PPCharacterAttributeSet.h"
#include "GameplayEffectExtension.h"

void UPPCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
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
}
