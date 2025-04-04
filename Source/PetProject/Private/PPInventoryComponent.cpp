// Fill out your copyright notice in the Description page of Project Settings.

#include "PPInventoryComponent.h"
#include "Weapons/PPBaseWeapon.h"
#include "ItemData/PPItemData.h"

UPPInventoryComponent::UPPInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

UPPInventoryComponent* UPPInventoryComponent::GetInventoryComponentFromActor(const AActor* InActor)
{
	if (IsValid(InActor))
	{
		return InActor->FindComponentByClass<UPPInventoryComponent>();
	}

	return nullptr;
}

void UPPInventoryComponent::AddItem(UPPItem* Item, FPPItemData ItemData, bool bAutoSlot)
{
	Inventory.Add(Item, ItemData);

	if (bAutoSlot)
	{
		FillEmptySlotWithItem(Item);
	}
}

void UPPInventoryComponent::SetSlottedItem(UPPItem* Item, FPPItemSlot ItemSlot)
{
	for (TPair<FPPItemSlot, UPPItem*>& Elem : SlottedItems)
	{
		if (Elem.Key == ItemSlot)
		{
			Elem.Value = Item;
		}
		//else if (IsValid(Item) && Elem.Value == Item)
		//{
		//	Elem.Value = nullptr;
		//}
	}

	OnSlottedItemChangedDelegateHandle.Broadcast(Item, ItemSlot);
}

void UPPInventoryComponent::FillEmptySlotWithItem(UPPItem* Item)
{
	FPPItemSlot ItemSlot;

	for (TPair<FPPItemSlot, UPPItem*>& Elem : SlottedItems)
	{
		if (Elem.Key.ItemType == Item->ItemType)
		{
			if (Elem.Value == Item)
			{
				return;
			}
			else if (Elem.Value == nullptr && (!ItemSlot.IsValid() || ItemSlot.SlotNumber > Elem.Key.SlotNumber))
			{
				ItemSlot = Elem.Key;
				break;
			}
		}
	}
	
	if (ItemSlot.IsValid())
	{
		SlottedItems[ItemSlot] = Item;
		SetActiveItem(ItemSlot);
	}
	
	OnSlottedItemChangedDelegateHandle.Broadcast(Item, ItemSlot);
}

void UPPInventoryComponent::GetSlottedItemsByType(TArray<UPPItem*>& Items, EItemType ItemType)
{
	for (TPair<FPPItemSlot, UPPItem*>& Elem : SlottedItems)
	{
		if (Elem.Key.ItemType == ItemType)
		{
			Items.Add(Elem.Value);
		}
	}
}

void UPPInventoryComponent::GetAllSlottedItems(TArray<UPPItem*>& Items)
{
	for (TPair<FPPItemSlot, UPPItem*>& Elem : SlottedItems)
	{
		if (IsValid(Elem.Value))
		{
			Items.Add(Elem.Value);
		}
	}
}

FPPItemData UPPInventoryComponent::GetItemData(UPPItem* Item)
{
	FPPItemData* Data = Inventory.Find(Item);
	
	if (Data)
	{
		return *Data;
	}

	return FPPItemData();
}

void UPPInventoryComponent::ConsumeItem(UPPItem* InItem, int32 Count, bool bShouldRemove)
{
	FPPItemData* ItemData = Inventory.Find(InItem);
	
	if (!ItemData)
	{
		return;
	}

	ItemData->ItemCount = FMath::Clamp(ItemData->ItemCount, 0, ItemData->ItemCount - Count);

	if (bShouldRemove && ItemData->ItemCount <= 0)
	{
		RemoveItem(InItem);
		return;
	}
	
	Inventory.Add(InItem, *ItemData);
	OnInventoryItemChangedDelegateHandle.Broadcast(InItem, *ItemData);
}

void UPPInventoryComponent::RemoveItem(UPPItem* InItem)
{
	Inventory.Remove(InItem);
	
	for (auto& Elem : SlottedItems)
	{
		if (Elem.Value == InItem)
		{
			OnSlottedItemChangedDelegateHandle.Broadcast(Elem.Value, Elem.Key);
			Elem.Value = nullptr;
		}
	}
}

TSubclassOf<UGameplayAbility> UPPInventoryComponent::GetItemAbility(EItemType ItemType)
{
	UPPItem* Item = GetActiveItemByType(ItemType);

	if (IsValid(Item))
	{
		return Item->GrantedAbility;
	}

	return TSubclassOf<UGameplayAbility>();
}

void UPPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitSlottedItems();
}

void UPPInventoryComponent::SetActiveItem(FPPItemSlot Slot)
{
	ActiveItems.Add(Slot.ItemType, Slot.SlotNumber);

	UPPItem** Item = SlottedItems.Find(Slot);

	OnActiveItemChangedDelegateHandle.Broadcast(*Item);
}

int32 UPPInventoryComponent::GetActiveItemIndexByType(EItemType Type)
{
	int32* Index = ActiveItems.Find(Type);

	return Index ? *Index : 0;
}

UPPItem* UPPInventoryComponent::GetActiveItemByType(EItemType Type)
{
	int32* Index = ActiveItems.Find(Type);

	if (Index)
	{
		FPPItemSlot Slot(Type, *Index);
		UPPItem** Item = SlottedItems.Find(Slot);

		if (Item)
		{
			return *Item;
		}
	}

	return nullptr;
}

void UPPInventoryComponent::InitSlottedItems()
{
	for (TPair<EItemType, int32> Elem : ItemSlotsPerType)
	{
		for (int32 SlotNumber = 0; SlotNumber < Elem.Value; ++SlotNumber)
		{
			SlottedItems.Add(FPPItemSlot(Elem.Key, SlotNumber), nullptr);
		}
	}
}

int32 UPPInventoryComponent::GetItemCount(UPPItem* InItem)
{
	FPPItemData* ItemData = Inventory.Find(InItem);
	
	if (ItemData)
	{
		return ItemData->ItemCount;
	}

	return 0;
}