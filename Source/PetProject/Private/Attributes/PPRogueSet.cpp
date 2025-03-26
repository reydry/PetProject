// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/PPRogueSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"

void UPPRogueSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetEffectContext();
		AActor* Instigator = EffectContextHandle.GetInstigator();

		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		OnHealthChangedDelegate.Broadcast(Instigator, GetHealth(), GetMaxHealth());

		if (FMath::IsNearlyZero(GetHealth()))
		{
			FGameplayEventData Payload;

			Payload.EventTag = FGameplayTag::RequestGameplayTag("Ability.Death");
			Payload.Instigator = Instigator;
			Payload.Target = GetOwningActor();

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningActor(), FGameplayTag::RequestGameplayTag("Ability.Death"), Payload);
		}
	}
}
