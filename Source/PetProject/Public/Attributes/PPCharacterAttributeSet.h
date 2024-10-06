// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PPCharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegateSignature);

UCLASS()
class PETPROJECT_API UPPCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, Health);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, MaxStamina);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxStamina);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxStamina);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxStamina);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, Stamina);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Stamina);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Stamina);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Stamina);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, MaxMana);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxMana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxMana);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxMana);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, Mana);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Mana);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Mana);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, Vigor);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Vigor);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Vigor);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Vigor);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, Endurance);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Endurance);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Endurance);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Endurance);

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ThisClass, Mind);
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Mind);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Mind);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mind);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnDeathDelegateSignature OnDeathDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Mana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Vigor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Endurance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Mind;
};
