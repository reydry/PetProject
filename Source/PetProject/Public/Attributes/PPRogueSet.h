// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/PPAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PPRogueSet.generated.h"

UCLASS()
class PETPROJECT_API UPPRogueSet : public UPPAttributeSet
{
	GENERATED_BODY()
	
public:
	ATTRIBUTE_ACCESSORS(UPPRogueSet, Health);
	ATTRIBUTE_ACCESSORS(UPPRogueSet, MaxHealth);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
};
