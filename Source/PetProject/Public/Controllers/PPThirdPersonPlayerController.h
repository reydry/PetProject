// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPThirdPersonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UPPInventoryComponent;
struct FInputActionValue;

UCLASS()
class PETPROJECT_API APPThirdPersonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APPThirdPersonPlayerController();

protected:
	void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	TObjectPtr<UPPInventoryComponent> InventoryComponent;
};
