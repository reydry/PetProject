// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PPPlayerCharacter.h"
#include "Components/PPCameraLockComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PPHeroComponent.h"

APPPlayerCharacter::APPPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	CameraLockComponent = CreateDefaultSubobject<UPPCameraLockComponent>(TEXT("CameraLockComponent"));

	HeroComponent = CreateDefaultSubobject<UPPHeroComponent>(TEXT("HeroComponent"));
}

void APPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (IsValid(HeroComponent))
	{
		HeroComponent->InitializePlayerInput(PlayerInputComponent);
	}
}

