// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerState/PPRLPlayerState.h"
#include "Attributes/PPWeaponSet.h"
#include "Attributes/PPRogueSet.h"

APPRLPlayerState::APPRLPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WeaponSet = CreateDefaultSubobject<UPPWeaponSet>("WeaponSet");
	RogueSet = CreateDefaultSubobject<UPPRogueSet>("RogueSet");
}

UPPWeaponSet* APPRLPlayerState::GetWeaponSet()
{
	return WeaponSet;
}

UPPRogueSet* APPRLPlayerState::GetRogueSet()
{
	return RogueSet;
}
