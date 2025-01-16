// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PPCharacter.h"
#include "PlayerState/PPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "ItemData/PPItemData.h"
#include "Components/PPCameraLockComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Attributes/PPCharacterSet.h"
#include "Components/PPHeroComponent.h"

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

void APPCharacter::SetupAbilities()
{
	for (TPair<TSubclassOf<UGameplayAbility>, EPPAbilityInputID>& Ability : Abilities)
	{
		GiveAbility(Ability.Key, 0, static_cast<int32>(Ability.Value));
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

void APPCharacter::GiveAbility(TSubclassOf<UGameplayAbility> InAbility, int32 Level, int32 InputID)
{
	if (IsValid(AbilitySystemComponent) && IsValid(InAbility))
	{
		FGameplayAbilitySpec AbilitySpec(InAbility, Level, InputID);
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

void APPCharacter::RemoveAbilities()
{
	for (TTuple<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle>& Ability : GivenAbilities)
	{
		AbilitySystemComponent->ClearAbility(Ability.Value);
	}
}

UAbilitySystemComponent* APPCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (IsValid(HeroComponent))
	{
		HeroComponent->InitializePlayerInput(PlayerInputComponent);
	}
}
