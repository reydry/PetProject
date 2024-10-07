// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PPPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerState.h"
#include "PlayerState/PPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attributes/PPCharacterSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PPInventoryComponent.h"
#include "ItemData/PPItemData.h"
#include "Components/PPCameraLockComponent.h"

APPPlayerCharacter::APPPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	InventoryComponent = CreateDefaultSubobject<UPPInventoryComponent>(TEXT("InventoryComponent"));
	CameraLockComponent = CreateDefaultSubobject<UPPCameraLockComponent>(TEXT("CameraLockComponent"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APPPlayerCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (FMath::IsNearlyZero(Data.NewValue) && !bIsDummy)
	{
		Destroy();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("health = %f"), Data.NewValue));
}

UPPInventoryComponent* APPPlayerCharacter::GetInventoryComponent() const
{
	return InventoryComponent;
}

void APPPlayerCharacter::GiveAbilities()
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (!IsValid(AbilitySystem))
	{
		return;
	}

	for (TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability));
	
		GivenAbilities.Add(Ability, AbilitySpecHandle);
	}

	AbilitySystem->InitAbilityActorInfo(this, this);
}

void APPPlayerCharacter::InitDelegates()
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();
	UPPCharacterSet* AttributeSet = GetAttributeSet();

	if (!IsValid(AbilitySystem) || !IsValid(AttributeSet))
	{
		return;
	}
	
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void APPPlayerCharacter::InitAttributes()
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (!IsValid(AbilitySystem) || !IsValid(DefaultAttributes))
	{
		return;
	}

	AbilitySystem->ApplyGameplayEffectToSelf(DefaultAttributes.GetDefaultObject(), 1, FGameplayEffectContextHandle());
}

bool APPPlayerCharacter::IsAbilityActive(TSubclassOf<UGameplayAbility> InAbilityClass)
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (!IsValid(InAbilityClass) || !IsValid(AbilitySystem))
	{
		return false;
	}

	FGameplayAbilitySpec* Spec = AbilitySystem->FindAbilitySpecFromClass(InAbilityClass);

	if (Spec)
	{
		return Spec->IsActive();
	}	

	return false;
}

void APPPlayerCharacter::ActivateAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (!IsValid(InAbility))
	{
		return;
	}

	FGameplayAbilitySpecHandle Ability = *GivenAbilities.Find(InAbility);
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (IsValid(AbilitySystem))
	{
		AbilitySystem->TryActivateAbility(Ability);
	}
}

void APPPlayerCharacter::CancelAbility(TSubclassOf<UGameplayAbility> InAbility)
{
	if (!IsValid(InAbility))
	{
		return;
	}

	FGameplayAbilitySpecHandle Ability = *GivenAbilities.Find(InAbility);
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();

	if (IsValid(AbilitySystem))
	{
		AbilitySystem->CancelAbilityHandle(Ability);
	}
}

void APPPlayerCharacter::PossessedBy(AController* InController)
{
	Super::PossessedBy(InController);

	GiveAbilities();
	InitDelegates();
	InitAttributes();
}

UAbilitySystemComponent* APPPlayerCharacter::GetAbilitySystemComponent() const 
{
	APPPlayerState* State = GetPlayerState<APPPlayerState>();

	if (IsValid(State))
	{
		return State->GetAbilitySystemComponent();
	}

	return nullptr;
}

UPPCharacterSet* APPPlayerCharacter::GetAttributeSet() const
{
	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponent();
	
	if (IsValid(AbilitySystem))
	{
		return const_cast<UPPCharacterSet*>(AbilitySystem->GetSet<UPPCharacterSet>());
	}

	return nullptr;
}

