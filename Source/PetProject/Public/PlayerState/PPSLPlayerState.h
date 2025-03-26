// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/PPPlayerState.h"
#include "PPSLPlayerState.generated.h"

class UPPCharacterSet;
class UPPSoulsSet;
class UPPWeaponSet;

UCLASS(BlueprintType, Blueprintable, notplaceable)
class PETPROJECT_API APPSLPlayerState : public APPPlayerState
{
	GENERATED_BODY()
	
public:
	APPSLPlayerState(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	UPPCharacterSet* GetCharacterSet();
	
	UFUNCTION(BlueprintPure)
	UPPSoulsSet* GetSoulsSet();

private:
	UPROPERTY()
	UPPCharacterSet* CharacterSet;
	
	UPROPERTY()
	UPPSoulsSet* SoulsSet;
};
