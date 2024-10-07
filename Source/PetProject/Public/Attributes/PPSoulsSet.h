// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/PPAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PPSoulsSet.generated.h"

UCLASS()
class PETPROJECT_API UPPSoulsSet : public UPPAttributeSet
{
	GENERATED_BODY()
	
public:
	UPPSoulsSet();

	ATTRIBUTE_ACCESSORS(UPPSoulsSet, Vigor);
	ATTRIBUTE_ACCESSORS(UPPSoulsSet, Mind);
	ATTRIBUTE_ACCESSORS(UPPSoulsSet, Endurance);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Vigor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mind;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Endurance;
};
