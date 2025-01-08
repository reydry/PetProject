// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "PPinventoryComponent.h"
#include "PPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;
class UPPCharacterSet;
class UPPCameraLockComponent;
class UInputComponent;

UCLASS()
class PETPROJECT_API APPCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APPCharacter();

	virtual void PossessedBy(AController* InController) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION(BlueprintCallable)
	void GiveAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	void RemoveAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	bool IsAbilityActive(TSubclassOf<UGameplayAbility> InAbilityClass);

	UFUNCTION(BlueprintCallable)
	void ActivateAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	void ActivateAbilityWithTag(FGameplayTagContainer AbilityTagContainer);

	UFUNCTION(BlueprintCallable)
	void CancelAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	void RemoveAbilities();

	UPROPERTY(EditDefaultsOnly)
	bool bIsDummy = false;

	void SetupAbilities();

	void InitAbilitySystem(AController* InController);

	void GivePassiveAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTagContainer, TArray<UGameplayAbility*>& ActiveAbilities);

	UFUNCTION(BlueprintPure)
	TSubclassOf<UGameplayAbility> GetAbility(EItemType ItemType);

private:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY()
	UPPCameraLockComponent* CameraLockComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> PassiveAbilities;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle> GivenAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayEffect>> Effects;
};
