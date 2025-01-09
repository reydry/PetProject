// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PPHeroComponent.h"
#include "Utils/PPUtils.h"
#include "AbilitySystemComponent.h"
#include "Characters/PPCharacter.h"

UPPHeroComponent::UPPHeroComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UPPHeroComponent* UPPHeroComponent::GetHeroComponent(const AActor* Actor)
{
	return Actor ? Actor->FindComponentByClass<UPPHeroComponent>() : nullptr;
}

void UPPHeroComponent::AddAdditionalInputConfig(UPPAbilityInputConfig* InputConfig)
{
	if (APawn* Pawn = GetOwner<APawn>())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent))
		{
			for (auto Input : InputConfig->Inputs)
			{
				FInputBindingHandle BindingHandle = EnhancedInputComponent->BindAction(Input.InputAction, Input.TriggerEvent, this, &UPPHeroComponent::AbilityInputPressed, static_cast<int32>(Input.AbilityInputID));
				TemporaryBindings.Add(Input.AbilityInputID, BindingHandle);
			}
		}
	}
}

void UPPHeroComponent::RemoveInputConfig(UPPAbilityInputConfig* InputConfig)
{
	if (APawn* Pawn = GetOwner<APawn>())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent))
		{
			for (auto Input : InputConfig->Inputs)
			{
				FInputBindingHandle BindingHandle = *TemporaryBindings.Find(Input.AbilityInputID);
				EnhancedInputComponent->RemoveBinding(BindingHandle);
			}
		}
	}
}

void UPPHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	APPCharacter* Character = GetOwner<APPCharacter>();

	if (!IsValid(Character))
	{
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	UPPAbilityInputConfig* InputConfig = Character->GetInputConfig();
	
	if (!IsValid(InputConfig) || !IsValid(EnhancedInputComponent))
	{
		return;
	}

	for (auto Input : InputConfig->Inputs)
	{
		if(!Input.bPassive)
		EnhancedInputComponent->BindAction(Input.InputAction, Input.TriggerEvent, this, &ThisClass::AbilityInputPressed, static_cast<int32>(Input.AbilityInputID));
	}
}

void UPPHeroComponent::AbilityInputPressed(int32 InputID)
{
	if (APPCharacter* Character = GetOwner<APPCharacter>())
	{
		if (UAbilitySystemComponent* AbilitySystem = Character->GetAbilitySystemComponent())
		{
			AbilitySystem->PressInputID(InputID);
		}
	}
}

void UPPHeroComponent::AbilityInputReleased(int32 InputID)
{
	if (APPCharacter* Character = GetOwner<APPCharacter>())
	{
		if (UAbilitySystemComponent* AbilitySystem = Character->GetAbilitySystemComponent())
		{
			AbilitySystem->ReleaseInputID(InputID);
		}
	}
}

void UPPHeroComponent::BeginPlay()
{
	Super::BeginPlay();
}
