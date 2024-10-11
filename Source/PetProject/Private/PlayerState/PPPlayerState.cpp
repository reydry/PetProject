// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attributes/PPSoulsSet.h"
#include "Attributes/PPCharacterSet.h"

APPPlayerState::APPPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	CharacterSet = CreateDefaultSubobject<UPPCharacterSet>("CharacterSet");
	SoulsSet = CreateDefaultSubobject<UPPSoulsSet>("SoulsSet");
}

UAbilitySystemComponent* APPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

