// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"

#include "PPPlayerState.generated.h"

class UPPCharacterSet;
class UPPSoulsSet;
class UPPWeaponSet;

UENUM(BlueprintType)
enum class EPPTeam : uint8
{
	None,
	Player,
	Bot
};

UCLASS()
class PETPROJECT_API APPPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APPPlayerState(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure)
	UPPCharacterSet* GetCharacterSet();

	UFUNCTION(BlueprintPure)
	bool IsAbilityActive(TSubclassOf<UGameplayAbility> InAbilityClass) const;

protected:
	virtual void BeginPlay() override;

	void SetupTeam();

	UPROPERTY(BlueprintReadOnly)
	EPPTeam Team = EPPTeam::None;

private:
	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UPPCharacterSet* CharacterSet;

	UPROPERTY()
	UPPWeaponSet* WeaponSet;
};
