// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerState/PPSLPlayerState.h"
#include "Attributes/PPSoulsSet.h"
#include "Attributes/PPCharacterSet.h"

APPSLPlayerState::APPSLPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CharacterSet = CreateDefaultSubobject<UPPCharacterSet>("CharacterSet");
	SoulsSet = CreateDefaultSubobject<UPPSoulsSet>("SoulsSet");
}

UPPCharacterSet* APPSLPlayerState::GetCharacterSet()
{
	return CharacterSet;
}

UPPSoulsSet* APPSLPlayerState::GetSoulsSet()
{
	return SoulsSet;
}
