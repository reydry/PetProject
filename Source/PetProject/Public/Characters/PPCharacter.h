// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "PPinventoryComponent.h"
#include "Utils/PPUtils.h"
#include "PPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;
class UPPCharacterSet;
class UInputComponent;
class UPPAbilityInputConfig;

UCLASS()
class PETPROJECT_API APPCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APPCharacter();

	virtual void PossessedBy(AController* InController) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UFUNCTION(BlueprintCallable)
	void GiveAbility(TSubclassOf<UGameplayAbility> InAbility, int32 Level, int32 InputID);

	UFUNCTION(BlueprintCallable)
	void RemoveAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	void RemoveAbilities();

	UPROPERTY(EditDefaultsOnly)
	bool bIsDummy = false;

	void InitAbilitySystem(AController* InController);

	UFUNCTION(BlueprintCallable)
	void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTagContainer, TArray<UGameplayAbility*>& ActiveAbilities);

	void SetupAbilities();

	UFUNCTION(BlueprintPure)
	TSubclassOf<UGameplayAbility> GetAbility(EItemType ItemType);

private:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<UGameplayAbility>, EPPAbilityInputID> Abilities;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle> GivenAbilities;
};
