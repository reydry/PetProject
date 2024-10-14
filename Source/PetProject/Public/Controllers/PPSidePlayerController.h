// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/PPPlayerController.h"
#include "PPSidePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PETPROJECT_API APPSidePlayerController : public APPPlayerController
{
	GENERATED_BODY()
	
public:
	APPSidePlayerController();

protected:
	virtual void MoveInput(const FInputActionValue& InputActionValue) override;
};
