// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PPCharacter.h"
#include "PPPlayerCharacter.generated.h"

class UPPInteractionComponent;
class UPPHeroComponent;
class UPPCameraLockComponent;
class USphereComponent;

UCLASS()
class PETPROJECT_API APPPlayerCharacter : public APPCharacter
{
	GENERATED_BODY()

public:
	APPPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* TopDownCameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPPCameraLockComponent* CameraLockComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPPHeroComponent* HeroComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPPInteractionComponent* InteractionComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent = nullptr;
};
