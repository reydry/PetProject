// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PPCharacter.h"
#include "PlayerState/PPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "ItemData/PPItemData.h"
#include "Components/PPCameraLockComponent.h"

#include "Attributes/PPCharacterSet.h"

APPCharacter::APPCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraLockComponent = CreateDefaultSubobject<UPPCameraLockComponent>(TEXT("CameraLockComponent"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APPCharacter::PossessedBy(AController* InController)
{
	Super::PossessedBy(InController);

	InitAbilitySystem(InController);
	SetupAbilities();
}

void APPCharacter::InitAbilitySystem(AController* InController)
{
	APPPlayerState* State = InController->GetPlayerState<APPPlayerState>();

	if (!IsValid(State))
	{
		return;
	}

	AbilitySystemComponent = State->GetAbilitySystemComponent();

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void APPCharacter::GivePassiveAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InAbility))
	{
		FGameplayAbilitySpec AbilitySpec(InAbility);
		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		GivenAbilities.Add(InAbility, AbilitySpecHandle);
	}
}

void APPCharacter::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTagContainer, TArray<UGameplayAbility*>& ActiveAbilities)
{
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagContainer, AbilitiesToActivate, false);

	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* Ability : AbilityInstances)
		{
			ActiveAbilities.Add(Ability);
		}
	}
}

TSubclassOf<UGameplayAbility> APPCharacter::GetAbility(EItemType ItemType)
{
	UPPInventoryComponent* InventoryComponent = UPPInventoryComponent::GetInventoryComponentFromActor(GetController());

	if (IsValid(InventoryComponent))
	{
		return InventoryComponent->GetItemAbility(ItemType);
	}

	return TSubclassOf<UGameplayAbility>();
}

void APPCharacter::GiveAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InAbility))
	{
		FGameplayAbilitySpec AbilitySpec(InAbility);
		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
		GivenAbilities.Add(InAbility, AbilitySpecHandle);
	}
}

void APPCharacter::RemoveAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InAbility))
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = *GivenAbilities.Find(InAbility);
		AbilitySystemComponent->ClearAbility(AbilitySpecHandle);
		GivenAbilities.Remove(InAbility);
	}
}

bool APPCharacter::IsAbilityActive(TSubclassOf<UGameplayAbility> InAbilityClass)
{
	if (!IsValid(InAbilityClass) || !IsValid(AbilitySystemComponent))
	{
		return false;
	}

	FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromClass(InAbilityClass);

	if (Spec)
	{
		return Spec->IsActive();
	}

	return false;
}

void APPCharacter::ActivateAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (!IsValid(InAbility) || !IsValid(AbilitySystemComponent))
	{
		return;
	}

	FGameplayAbilitySpecHandle* Ability = GivenAbilities.Find(InAbility);

	if (Ability)
	{
		AbilitySystemComponent->TryActivateAbility(*Ability);
	}
}

void APPCharacter::ActivateAbilityWithTag(FGameplayTagContainer AbilityTagContainer)
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTagContainer);
	}
}

void APPCharacter::CancelAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (!IsValid(InAbility) || !IsValid(AbilitySystemComponent))
	{
		return;
	}

	FGameplayAbilitySpecHandle *Ability = GivenAbilities.Find(InAbility);

	if (Ability)
	{
		AbilitySystemComponent->CancelAbilityHandle(*Ability);
	}
}

void APPCharacter::RemoveAbilities()
{
	for (TTuple<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle>& Ability : GivenAbilities)
	{
		AbilitySystemComponent->ClearAbility(Ability.Value);
	}
}

void APPCharacter::SetupAbilities()
{
	for (TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		GiveAbility(Ability);
	}

	for (TSubclassOf<UGameplayAbility>& PassiveAbility : PassiveAbilities)
	{
		GivePassiveAbility(PassiveAbility);
	}

}

UAbilitySystemComponent* APPCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
