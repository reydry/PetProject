// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PPHeroComponent.h"
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

void UPPHeroComponent::AddAdditionalInputConfig(UPPAbilityInputConfig* InConfig)
{
	if (APawn* Pawn = GetOwner<APawn>())
	{
		for (FPPAbilityInput& Input : InConfig->Inputs)
		{
			TArray<FInputBindingHandle> BindingHandles = BindAbilityAction(Input, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, Pawn->InputComponent);
			TemporaryBindings.Add(Input.AbilityInputID, BindingHandles);
		}
	}
}

void UPPHeroComponent::RemoveInputConfig(UPPAbilityInputConfig* InConfig)
{
	if (APawn* Pawn = GetOwner<APawn>())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent))
		{
			for (FPPAbilityInput& Input : InConfig->Inputs)
			{
				TArray<FInputBindingHandle>* BindingHandles = TemporaryBindings.Find(Input.AbilityInputID);
				
				if (BindingHandles)
				{
					for (FInputBindingHandle Handle : *BindingHandles)
					{
						EnhancedInputComponent->RemoveBinding(Handle);
					}
					
					TemporaryBindings.Remove(Input.AbilityInputID);
				}
			}
		}
	}
}

void UPPHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	if (!IsValid(InputConfig))
	{
		return;
	}
	
	for (FPPAbilityInput& Input : InputConfig->Inputs)
	{
		BindAbilityAction(Input, this, &ThisClass::AbilityInputPressed, &ThisClass::AbilityInputReleased, PlayerInputComponent);
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

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
TArray<FInputBindingHandle> UPPHeroComponent::BindAbilityAction(const FPPAbilityInput InInputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!IsValid(EnhancedInputComponent))
	{
		return TArray<FInputBindingHandle>();
	}

	TArray<FInputBindingHandle> BindingHandles;

	if (ReleasedFunc)
	{
		BindingHandles.Add(EnhancedInputComponent->BindAction(InInputConfig.InputAction, InInputConfig.ReleasedEvent, this, &ThisClass::AbilityInputReleased, static_cast<int32>(InInputConfig.AbilityInputID)));
	}

	if (PressedFunc)
	{
		BindingHandles.Add(EnhancedInputComponent->BindAction(InInputConfig.InputAction, InInputConfig.PressedEvent, this, &ThisClass::AbilityInputPressed, static_cast<int32>(InInputConfig.AbilityInputID)));
	}

	return BindingHandles;
}