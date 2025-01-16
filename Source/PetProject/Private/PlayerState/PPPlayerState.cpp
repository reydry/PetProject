// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attributes/PPSoulsSet.h"
#include "Attributes/PPCharacterSet.h"
#include "Attributes/PPWeaponSet.h"

APPPlayerState::APPPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	CharacterSet = CreateDefaultSubobject<UPPCharacterSet>("CharacterSet");
	WeaponSet = CreateDefaultSubobject<UPPWeaponSet>("WeaponSet");
}

UAbilitySystemComponent* APPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UPPCharacterSet* APPPlayerState::GetCharacterSet()
{
	return CharacterSet;
}

bool APPPlayerState::IsAbilityActive(TSubclassOf<UGameplayAbility> InAbilityClass) const
{
	if (!IsValid(InAbilityClass) || !IsValid(AbilitySystemComponent))
	{
		return false;
	}

	FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromClass(InAbilityClass);

	if (Spec)
	{
		return Spec->IsActive();
	}

	return false;
}

void APPPlayerState::BeginPlay()
{
	Super::BeginPlay();

	SetupTeam();
}

void APPPlayerState::SetupTeam()
{
	if (IsABot())
	{
		Team = EPPTeam::Bot;
		return;
	}

	Team = EPPTeam::Player;
}

