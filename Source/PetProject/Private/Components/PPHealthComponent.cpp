// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PPHealthComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Attributes/PPCharacterSet.h"

UPPHealthComponent::UPPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

UPPHealthComponent* UPPHealthComponent::GetHealthComponentFromActor(const AActor* InActor)
{
	if (IsValid(InActor))
	{
		return InActor->FindComponentByClass<UPPHealthComponent>();
	}

	return nullptr;
}

void UPPHealthComponent::InitializeComponentData(UAbilitySystemComponent* InAbilitySystem)
{
	if (!IsValid(InAbilitySystem))
	{
		return;
	}

	CharacterSet = InAbilitySystem->GetSet<UPPCharacterSet>();

	if (!IsValid(CharacterSet))
	{
		return;
	}

	InAbilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void UPPHealthComponent::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChangedDelegateHandle.Broadcast(Data.NewValue, CharacterSet->GetMaxHealth(), Data.Attribute.AttributeName);
	
	if (FMath::IsNearlyZero(Data.NewValue))
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), FGameplayTag::RequestGameplayTag("Ability.Death"), FGameplayEventData());
	}
}
