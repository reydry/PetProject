// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/PPPlayerController.h"
#include "PPThirdPersonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UPPInventoryComponent;
struct FInputActionValue;

UCLASS()
class PETPROJECT_API APPThirdPersonPlayerController : public APPPlayerController
{
	GENERATED_BODY()
	
public:
	APPThirdPersonPlayerController();

protected:
	virtual void MoveInput(const FInputActionValue& InputActionValue) override;
	virtual void LookInput(const FInputActionValue& InputActionValue) override;
};
