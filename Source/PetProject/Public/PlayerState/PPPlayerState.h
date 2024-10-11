// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"

#include "PPPlayerState.generated.h"

class UPPCharacterSet;
class UPPSoulsSet;

UCLASS()
class PETPROJECT_API APPPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APPPlayerState(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UPPCharacterSet* CharacterSet;
	
	UPROPERTY()
	UPPSoulsSet* SoulsSet;
};
