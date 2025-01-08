// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PPPlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/KismetMathLibrary.h"

APPPlayerController::APPPlayerController()
{
	bShowMouseCursor = true;
}

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(Movement, ETriggerEvent::Triggered, this, &ThisClass::MoveInput);
		EnhancedInputComponent->BindAction(Look, ETriggerEvent::Triggered, this, &ThisClass::LookInput);
	}
}

void APPPlayerController::MoveInput(const FInputActionValue& InputActionValue)
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
		const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
		MyPawn->AddMovementInput(MovementDirection, Value.X);
	}

	if (Value.Y != 0.0f)
	{
		const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		MyPawn->AddMovementInput(MovementDirection, Value.Y);
	}
}

void APPPlayerController::LookInput(const FInputActionValue& InputActionValue)
{
	FHitResult Hit;
	FRotator CursorRotation(FRotator::ZeroRotator);
	APawn* MyPawn = Cast<APawn>(GetPawn());

	if (IsValid(MyPawn))
	{
		GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, Hit);
	
		CursorRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(), Hit.Location).Yaw;
		MyPawn->SetActorRotation(CursorRotation);
		SetControlRotation(CursorRotation);
	}
}
