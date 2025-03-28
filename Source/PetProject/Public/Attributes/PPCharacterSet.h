// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/PPAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PPCharacterSet.generated.h"

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

	ATTRIBUTE_ACCESSORS(UPPCharacterSet, Xperience);
	ATTRIBUTE_ACCESSORS(UPPCharacterSet, MaxXperience);
	
	ATTRIBUTE_ACCESSORS(UPPCharacterSet, Level);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Xperience;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxXperience;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Level;
};
