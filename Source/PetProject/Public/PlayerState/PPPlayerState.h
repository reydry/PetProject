// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"

#include "PPPlayerState.generated.h"

class UPPCharacterAttributeSet;

UCLASS()
class PETPROJECT_API APPPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APPPlayerState(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void SetupAbilitySystem();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UPPCharacterAttributeSet* CharacterAttributeSet;
	
};
