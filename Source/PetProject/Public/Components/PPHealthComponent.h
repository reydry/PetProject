// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPHealthComponent.generated.h"

class UPPCharacterSet;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangedDelegate, float, NewValue, float, MaxValue, FString, AttributeName);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PETPROJECT_API UPPHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPHealthComponent();

	UFUNCTION(BlueprintPure)
	static UPPHealthComponent* GetHealthComponentFromActor(const AActor* InActor);

	void InitializeComponentData(UAbilitySystemComponent* InAbilitySystem);

	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnManaChanged(const FOnAttributeChangeData& Data);
	void OnStaminaChanged(const FOnAttributeChangeData& Data);

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedDelegate OnAttributeChangedDelegateHandle;

private:
	UPROPERTY()
	TObjectPtr<const UPPCharacterSet> CharacterSet;
};
