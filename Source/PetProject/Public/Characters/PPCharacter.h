// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "PPCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;
class UPPCharacterSet;
class UPPHealthComponent;
class UPPCameraLockComponent;

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
	void GiveAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	void RemoveAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	bool IsAbilityActive(TSubclassOf<UGameplayAbility> InAbilityClass);

	UFUNCTION(BlueprintCallable)
	void ActivateAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	void CancelAbility(TSubclassOf<UGameplayAbility> InAbility);

	UFUNCTION(BlueprintCallable)
	void RemoveAbilities();

	UPROPERTY(EditDefaultsOnly)
	bool bIsDummy = false;

	void SetupAbilities();
	void SetupHealthComponent();

	void InitAbilitySystem(AController* InController);

	void GivePassiveAbility(TSubclassOf<UGameplayAbility> InAbility);

private:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY()
	UPPHealthComponent* HealthComponent = nullptr;

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

	UPROPERTY()
	UPPCameraLockComponent* CameraLockComponent = nullptr;
};
