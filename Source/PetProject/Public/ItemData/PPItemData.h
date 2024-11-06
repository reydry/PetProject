// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPInventoryComponent.h"
#include "PPItemData.generated.h"

class UGameplayAbility;
class APPBaseWeapon;

UCLASS(Abstract, BlueprintType)
class PETPROJECT_API UPPItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPPItem() {};

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EItemType ItemType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<AActor> ItemActor;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> GrantedAbility;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 MaxCount = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 BulletsInCartridge = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 Count = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTexture2D* Icon = nullptr;

	UFUNCTION(BlueprintPure)
	bool IsConsumable() const;

	UFUNCTION(BlueprintPure)
	bool IsWeapon() const;

	UFUNCTION(BlueprintPure)
	bool IsSpell() const;
};
