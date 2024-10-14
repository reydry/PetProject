// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PETPROJECT_API APPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APPPlayerController();

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;
	
	virtual void MoveInput(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintCallable)
	virtual void LookInput(const FInputActionValue& InputActionValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Look;
};
