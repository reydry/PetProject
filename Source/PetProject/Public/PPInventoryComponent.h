// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapons/PPBaseWeapon.h"
#include "PPInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChangedDelegate, UPPItem*, Item, int32, SlotNumber);

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
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemCount;
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
	void GetSlottedItems(TArray<UPPItem*>& Items, EItemType ItemType);

	UPROPERTY(BlueprintAssignable)
	FOnSlottedItemChangedDelegate OnSlottedItemChangedDelegateHandle;

protected:
	virtual void BeginPlay() override;

	void InitSlottedItems();

private:
	//non-equipped items
	TMap<UPPItem*, FPPItemData> Inventory;
	
	//equipped items
	TMap<FPPItemSlot, UPPItem*> SlottedItems;

	UPROPERTY(EditDefaultsOnly)
	TMap<EItemType, int32> ItemSlotsPerType;
};
