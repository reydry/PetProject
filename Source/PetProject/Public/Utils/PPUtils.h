// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h" 
#include "PPUtils.generated.h"

class UGameplayAbility;

UENUM()
enum class EPPAbilityInputID
{
	None,
	Primary_Single,
	Primary_Auto,
	Secondary,
	Dash,
	Ultimate_Aim,
	Ultimate_Fire,
	Collect,
	QuickReload,
};

USTRUCT()
struct FPPAbilityInput
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EPPAbilityInputID AbilityInputID = EPPAbilityInputID::None;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	ETriggerEvent PressedEvent = ETriggerEvent::None;

	UPROPERTY(EditDefaultsOnly)
	ETriggerEvent ReleasedEvent = ETriggerEvent::None;
};

UCLASS(BlueprintType)
class UPPAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FPPAbilityInput> Inputs;
};

UCLASS(BlueprintType, Blueprintable)
class UPPUtils : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Utils|Trace")
	static FVector CalculateEndLine(const APlayerController* InController);

private:
	static FVector GetLocationUnderCursor(const APlayerController* InController);
	static FVector GetCameraLocation(const APlayerController* InController);
};