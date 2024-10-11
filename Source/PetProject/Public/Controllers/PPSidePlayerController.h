// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPSidePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PETPROJECT_API APPSidePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APPSidePlayerController();

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	void MoveInput(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Movement;
};
