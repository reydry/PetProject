// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "PPPlayerCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;
class UPPCharacterSet;
class UPPInventoryComponent;
class UPPCameraLockComponent;

UCLASS(Blueprintable)
class PETPROJECT_API APPPlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APPPlayerCharacter();

	void OnHealthChanged(const FOnAttributeChangeData& Data);

	virtual void PossessedBy(AController* InController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPPCharacterSet* GetAttributeSet() const;

	UFUNCTION(BlueprintPure)
	UPPInventoryComponent* GetInventoryComponent() const;

protected:
	void GiveAbilities();
	void InitDelegates();
	void InitAttributes();

	UFUNCTION(BlueprintCallable)
	bool IsAbilityActive(TSubclassOf<UGameplayAbility> InAbilityClass);

	UFUNCTION(BlueprintCallable)
	void ActivateAbility(TSubclassOf<UGameplayAbility> InAbility);
	
	UFUNCTION(BlueprintCallable)
	void CancelAbility(TSubclassOf<UGameplayAbility> InAbility);

	UPROPERTY(BlueprintReadWrite)
	UPPInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly)
	bool bIsDummy = false;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<TSubclassOf<UGameplayAbility>, FGameplayAbilitySpecHandle> GivenAbilities;

	UPROPERTY()
	UPPCameraLockComponent* CameraLockComponent;
};
