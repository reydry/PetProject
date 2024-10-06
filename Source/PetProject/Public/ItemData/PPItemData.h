// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PPItemData.generated.h"

class UGameplayAbility;
class APPBaseWeapon;

UENUM()
enum class EItemType
{
	None = 0,
	Weapon = 1,
};

UCLASS(Abstract, BlueprintType)
class PETPROJECT_API UPPItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPPItemData() {};
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
	FString GetIdentifierString() const;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FPrimaryAssetType ItemType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<APPBaseWeapon> ItemActor;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> GrantedAbility;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 MaxCount = 1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 BulletsInCartridge = 1;
};
