// Fill out your copyright notice in the Description page of Project Settings.

#include "Attributes/PPCharacterSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"

UPPCharacterSet::UPPCharacterSet()
{

}

void UPPCharacterSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
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

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));

		OnStaminaChangedDelegate.Broadcast(GetStamina(), GetMaxStamina());
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		OnManaChangedDelegate.Broadcast(GetMana(), GetMaxMana());
	}

	if (Data.EvaluatedData.Attribute == GetXperienceAttribute())
	{
		SetXperience(FMath::Clamp(GetXperience(), 0.0f, GetMaxXperience()));

		if (FMath::IsNearlyEqual(GetXperience(), GetMaxXperience()))
		{
			OnLevelUpDelegate.Broadcast();
		}
	}
}
