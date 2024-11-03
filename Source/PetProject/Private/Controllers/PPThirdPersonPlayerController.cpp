// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/PPThirdPersonPlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

APPThirdPersonPlayerController::APPThirdPersonPlayerController()
{
	bShowMouseCursor = false;
}

void APPThirdPersonPlayerController::MoveInput(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn* PlayerPawn = GetPawn<APawn>();

	if (IsValid(PlayerPawn))
	{
		PlayerPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		PlayerPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APPThirdPersonPlayerController::LookInput(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	APawn* PlayerPawn = GetPawn<APawn>();

	if (IsValid(PlayerPawn))
	{
		PlayerPawn->AddControllerYawInput(LookAxisVector.X);
		PlayerPawn->AddControllerPitchInput(-LookAxisVector.Y);
	}
}
