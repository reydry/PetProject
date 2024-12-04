// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/PPBaseWeapon.h"
#include "PPInventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	Weapon,
	Consumable,
	Spell,
};

USTRUCT(BlueprintType)
struct FPPItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType = EItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemCount = 0;
};

USTRUCT(BlueprintType)
struct FPPItemSlot
{
	GENERATED_BODY()

	FPPItemSlot() : ItemType(EItemType::None), SlotNumber(-1) { }

	FPPItemSlot(EItemType InItemType, int32 InSlotNumber) : ItemType(InItemType), SlotNumber(InSlotNumber) { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotNumber;

	friend inline uint32 GetTypeHash(const FPPItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);

		return Hash;
	}

	bool operator==(const FPPItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}

	bool IsValid() const
	{
		return ItemType != EItemType::None && SlotNumber >= 0;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChangedDelegate, UPPItem*, Item, FPPItemSlot, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedDelegate, UPPItem*, Item, FPPItemData, ItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveItemChangedDelegate, UPPItem*, Item);

class UGameplayAbility;

UCLASS(BlueprintType, Blueprintable)
class PETPROJECT_API UPPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPInventoryComponent();

	UFUNCTION(BlueprintPure)
	static UPPInventoryComponent* GetInventoryComponentFromActor(const AActor* InActor);

	UFUNCTION(BlueprintCallable)
	void AddItem(UPPItem* Item, FPPItemData ItemData, bool bAutoSlot);

	void SetSlottedItem(UPPItem* Item, FPPItemSlot ItemSlot);
	
	void FillEmptySlotWithItem(UPPItem* Item);

	UFUNCTION(BlueprintPure)
	void GetSlottedItemsByType(TArray<UPPItem*>& Items, EItemType ItemType);

	UFUNCTION(BlueprintPure)
	void GetAllSlottedItems(TArray<UPPItem*>& Items);

	UFUNCTION(BlueprintPure)
	FPPItemData GetItemData(UPPItem* Item);

	UFUNCTION(BlueprintCallable)
	void ConsumeItem(UPPItem* InItem, int32 Count, bool bShouldRemove);

	void RemoveItem(UPPItem* InItem);

	TSubclassOf<UGameplayAbility> GetItemAbility(EItemType ItemType);

	UFUNCTION(BlueprintPure)
	int32 GetItemCount(UPPItem* InItem);

	UPROPERTY(BlueprintAssignable)
	FOnSlottedItemChangedDelegate OnSlottedItemChangedDelegateHandle;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemChangedDelegate OnInventoryItemChangedDelegateHandle;

	UPROPERTY(BlueprintAssignable)
	FOnActiveItemChangedDelegate OnActiveItemChangedDelegateHandle;

	UFUNCTION(BlueprintCallable)
	void SetActiveItem(FPPItemSlot Slot);

	UFUNCTION(BlueprintPure)
	int32 GetActiveItemIndexByType(EItemType Type);

	UFUNCTION(BlueprintPure)
	UPPItem* GetActiveItemByType(EItemType Type);

protected:
	virtual void BeginPlay() override;

	void InitSlottedItems();

private:
	//non-equipped items
	TMap<UPPItem*, FPPItemData> Inventory;

	//equipped items
	UPROPERTY()
	TMap<FPPItemSlot, UPPItem*> SlottedItems;

	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, int32> ItemSlotsPerType;

	TMap<EItemType, int32> ActiveItems;
};
