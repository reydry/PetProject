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

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	void MoveInput(const FInputActionValue& InputActionValue);

	UFUNCTION(BlueprintCallable)
	void LookInput(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Look;
};
