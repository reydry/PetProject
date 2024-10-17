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
	}
	
	OnSlottedItemChangedDelegateHandle.Broadcast(Item, ItemSlot.SlotNumber);
}

void UPPInventoryComponent::GetSlottedItems(TArray<UPPItem*>& Items, EItemType ItemType)
{
	for (TPair<FPPItemSlot, UPPItem*>& Elem : SlottedItems)
	{
		if (Elem.Key.ItemType == ItemType)
		{
			Items.Add(Elem.Value);
		}
	}
}

void UPPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitSlottedItems();
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
