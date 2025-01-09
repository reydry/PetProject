// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h" 
#include "PPUtils.generated.h"

class UGameplayAbility;

UENUM()
enum class PPAbilityInputID
{
	None,
	Ability1,
	Ability2,
	Ability3
};

USTRUCT()
struct FPPAbilityInput
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	PPAbilityInputID AbilityInputID = PPAbilityInputID::None;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	ETriggerEvent TriggerEvent = ETriggerEvent::None;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly)
	bool bPassive = false;
};

UCLASS(BlueprintType)
class UPPAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FPPAbilityInput> Inputs;

	//UPROPERTY(EditDefaultsOnly)
	//PPAbilityInputID AbilityInputID = PPAbilityInputID::None;

	//UPROPERTY(EditDefaultsOnly)
	//UInputAction* InputAction = nullptr;

	//UPROPERTY(EditDefaultsOnly)
	//ETriggerEvent TriggerEvent = ETriggerEvent::None;
	//PPAbilityInputID AbilityInputID = PPAbilityInputID::None;

	//UPROPERTY(EditDefaultsOnly)
	//PPAbilityInputID AbilityInputID = PPAbilityInputID::None;

	//UPROPERTY(EditDefaultsOnly)
	//PPAbilityInputID AbilityInputID = PPAbilityInputID::None;

	//UPROPERTY(EditDefaultsOnly)
	//PPAbilityInputID AbilityInputID = PPAbilityInputID::None;
	//
	//UPROPERTY(EditDefaultsOnly)
	//PPAbilityInputID AbilityInputID = PPAbilityInputID::None;

	//UPROPERTY(EditDefaultsOnly)
	//PPAbilityInputID AbilityInputID = PPAbilityInputID::None;
};
