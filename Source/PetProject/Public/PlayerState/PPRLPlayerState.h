// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/PPPlayerState.h"
#include "PPRLPlayerState.generated.h"

class UPPRogueSet;
class UPPWeaponSet;

UCLASS(BlueprintType, Blueprintable, notplaceable)
class PETPROJECT_API APPRLPlayerState : public APPPlayerState
{
	GENERATED_BODY()
	
public:
	APPRLPlayerState(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure)
	UPPWeaponSet* GetWeaponSet();
	
	UFUNCTION(BlueprintPure)
	UPPRogueSet* GetRogueSet();

private:
	UPROPERTY()
	UPPWeaponSet* WeaponSet;

	UPROPERTY()
	UPPRogueSet* RogueSet;
};
