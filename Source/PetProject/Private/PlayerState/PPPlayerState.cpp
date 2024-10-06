// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attributes/PPCharacterAttributeSet.h"

APPPlayerState::APPPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	CharacterAttributeSet = CreateDefaultSubobject<UPPCharacterAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* APPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APPPlayerState::SetupAbilitySystem()
{
	if(IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->AddAttributeSetSubobject(CharacterAttributeSet);
	}
}

void APPPlayerState::BeginPlay()
{
	Super::BeginPlay();
}
