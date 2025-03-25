// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PPAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChangedDelegateSignature, AActor*, Instigator, float, NewValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedDelegateSignature, float, NewValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangedDelegateSignature, float, NewValue, float, MaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpDelegateSignature);

UCLASS()
class PETPROJECT_API UPPAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPPAttributeSet();
	
	UWorld* GetWorld() const override;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnHealthChangedDelegateSignature OnHealthChangedDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnStaminaChangedDelegateSignature OnStaminaChangedDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnManaChangedDelegateSignature OnManaChangedDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnLevelUpDelegateSignature OnLevelUpDelegate;
};
