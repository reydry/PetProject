// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/PPSidePlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

APPSidePlayerController::APPSidePlayerController()
{
	bShowMouseCursor = false;
}

void APPSidePlayerController::MoveInput(const FInputActionValue& InputActionValue)
{
	APawn* MyPawn = GetPawn<APawn>();

	if (!IsValid(MyPawn))
	{
		return;
	}

	const FVector2D Value = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	if (Value.X != 0.0f)
	{
		const FVector MovementDirection = MovementRotation.RotateVector(FVector::LeftVector);
		MyPawn->AddMovementInput(MovementDirection, Value.X);
	}
}

