// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/PPBaseWeapon.h"
#include "PPInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemChangedDelegate, int32, PrevIndex, int32, NextWeapon);

class UPPItemData;

UCLASS(BlueprintType, Blueprintable)
class PETPROJECT_API UPPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPInventoryComponent();

	UFUNCTION(BlueprintPure)
	static UPPInventoryComponent* GetInventoryComponentFromActor(const AActor* InActor);

	UFUNCTION(BlueprintCallable)
	int32 AddItem(UPPItemData* Item);
	
	UFUNCTION(BlueprintCallable)
	void RemoveItem(UPPItemData* Item);

	UFUNCTION(BlueprintPure)
	UPPItemData* GetActiveItem() const;

	UFUNCTION(BlueprintCallable)
	void SetItem(int32 Index);

	UFUNCTION(BlueprintCallable)
	UPPItemData* GetNextWeapon();

	UFUNCTION(BlueprintCallable)
	int32 GetNextWeaponIndex();

	UFUNCTION(BlueprintPure)
	int32 GetItemCount(UPPItemData* ItemData);

	UFUNCTION(BlueprintPure)
	TSubclassOf<APPBaseWeapon> GetWeaponActor() const;

	UFUNCTION(BlueprintPure)
	TSubclassOf<UGameplayAbility> GetGrantedAbility() const;

	UPROPERTY(BlueprintAssignable)
	FOnItemChangedDelegate ActiveChangedDelegateHandle;

	UFUNCTION(BlueprintPure)
	UPPItemData* GetItemByIndex(int32 ItemIndex);

private:
	TMap<int32, UPPItemData*> InventoryData;
	
	int32 ActiveItemIndex = INDEX_NONE;
};
