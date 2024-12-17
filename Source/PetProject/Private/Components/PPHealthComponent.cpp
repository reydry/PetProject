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
	InAbilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetManaAttribute()).AddUObject(this, &ThisClass::OnManaChanged);
	InAbilitySystem->GetGameplayAttributeValueChangeDelegate(CharacterSet->GetStaminaAttribute()).AddUObject(this, &ThisClass::OnStaminaChanged);
}

void UPPHealthComponent::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChangedDelegateHandle.Broadcast(Data.NewValue, CharacterSet->GetMaxHealth(), Data.Attribute.AttributeName);
	
	if (FMath::IsNearlyZero(Data.NewValue))
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), FGameplayTag::RequestGameplayTag("Ability.Death"), FGameplayEventData());
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("health = %f"), Data.NewValue));
}

void UPPHealthComponent::OnManaChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChangedDelegateHandle.Broadcast(Data.NewValue, CharacterSet->GetMaxMana(), Data.Attribute.AttributeName);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("mana = %f"), Data.NewValue));
}

void UPPHealthComponent::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChangedDelegateHandle.Broadcast(Data.NewValue, CharacterSet->GetMaxStamina(), Data.Attribute.AttributeName);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("stamina = %f"), Data.NewValue));
}
