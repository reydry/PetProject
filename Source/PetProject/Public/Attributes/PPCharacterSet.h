// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/PPAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PPCharacterSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegateSignature);

UCLASS()
class PETPROJECT_API UPPCharacterSet : public UPPAttributeSet
{
	GENERATED_BODY()
	
public:
	UPPCharacterSet();

	ATTRIBUTE_ACCESSORS(UPPCharacterSet, Health);
	ATTRIBUTE_ACCESSORS(UPPCharacterSet, MaxHealth);

	ATTRIBUTE_ACCESSORS(UPPCharacterSet, Stamina);
	ATTRIBUTE_ACCESSORS(UPPCharacterSet, MaxStamina);

	ATTRIBUTE_ACCESSORS(UPPCharacterSet, Mana);
	ATTRIBUTE_ACCESSORS(UPPCharacterSet, MaxMana);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnDeathDelegateSignature OnDeathDelegate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;
};
