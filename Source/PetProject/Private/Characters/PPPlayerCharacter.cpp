// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PPPlayerCharacter.h"
#include "Components/PPCameraLockComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PPHeroComponent.h"
#include "Components/PPInteractionComponent.h"
#include "Components/SphereComponent.h"

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
	InteractionComponent = CreateDefaultSubobject<UPPInteractionComponent>(TEXT("InteractionComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("SphereComponent"));
}

void APPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (IsValid(HeroComponent))
	{
		HeroComponent->InitializePlayerInput(PlayerInputComponent);
	}
}

void APPPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (SphereComponent)
	{
		SphereComponent->SetSphereRadius(128.0f, true);
		SphereComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(InteractionComponent, &UPPInteractionComponent::OnBeginOverlap);
		SphereComponent->OnComponentEndOverlap.RemoveDynamic(InteractionComponent, &UPPInteractionComponent::OnEndOverlap);
	}
}

