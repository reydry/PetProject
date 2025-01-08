// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/PPAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PPWeaponSet.generated.h"

UCLASS()
class PETPROJECT_API UPPWeaponSet : public UPPAttributeSet
{
	GENERATED_BODY()
	
public:
	UPPWeaponSet();

	ATTRIBUTE_ACCESSORS(UPPWeaponSet, PrimaryAmmo);
	ATTRIBUTE_ACCESSORS(UPPWeaponSet, MaxPrimaryAmmo);

	ATTRIBUTE_ACCESSORS(UPPWeaponSet, SecondaryAmmo);
	ATTRIBUTE_ACCESSORS(UPPWeaponSet, MaxSecondaryAmmo);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData PrimaryAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxPrimaryAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData SecondaryAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxSecondaryAmmo;
	
};
