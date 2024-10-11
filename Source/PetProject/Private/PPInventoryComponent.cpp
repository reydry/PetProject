// Fill out your copyright notice in the Description page of Project Settings.

#include "PPInventoryComponent.h"
#include "Weapons/PPBaseWeapon.h"
#include "ItemData/PPItemData.h"

UPPInventoryComponent::UPPInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UPPInventoryComponent* UPPInventoryComponent::GetInventoryComponentFromActor(const AActor* InActor)
{
	if (IsValid(InActor))
	{
		return InActor->FindComponentByClass<UPPInventoryComponent>();
	}

	return nullptr;
}

void UPPInventoryComponent::SetItem(int32 Index)
{
	int32 PrevIndex = ActiveItemIndex;
	ActiveItemIndex = Index;
	ActiveChangedDelegateHandle.Broadcast(PrevIndex, ActiveItemIndex);
}

UPPItemData* UPPInventoryComponent::GetNextWeapon()
{
	return *InventoryData.Find(GetNextWeaponIndex());
}

int32 UPPInventoryComponent::GetNextWeaponIndex()
{
	//TODO: rewrite using Iterator
	int32 Index = ActiveItemIndex + 1; 

	if (Index > InventoryData.Num() - 1)
	{
		return 0;
	}

	return Index;
}

int32 UPPInventoryComponent::GetItemCount(UPPItemData* ItemData)
{
	return 0;
}

TSubclassOf<APPBaseWeapon> UPPInventoryComponent::GetWeaponActor() const
{
	if (ActiveItemIndex == INDEX_NONE)
	{
		return TSubclassOf<APPBaseWeapon>();
	}

	auto Item = *InventoryData.Find(ActiveItemIndex);
	
	return Item->ItemActor;
}

TSubclassOf<UGameplayAbility> UPPInventoryComponent::GetGrantedAbility() const
{
	if (ActiveItemIndex == INDEX_NONE)
	{
		return TSubclassOf<UGameplayAbility>();
	}

	auto Item = *InventoryData.Find(ActiveItemIndex);

	return Item->GrantedAbility;
}

UPPItemData* UPPInventoryComponent::GetItemByIndex(int32 ItemIndex)
{
	if (ItemIndex == INDEX_NONE)
	{
		return nullptr;
	}

	UPPItemData* Item = *InventoryData.Find(ItemIndex);

	return Item;
}

int32 UPPInventoryComponent::AddItem(UPPItemData* Item)
{
	if (Item)
	{
		int32 Num = InventoryData.Num();
	
		InventoryData.Add(Num, Item);

		return Num;
	}

	return INDEX_NONE;
}

void UPPInventoryComponent::RemoveItem(UPPItemData* Item)
{
	int32 Index = 0;

	for (const auto& Elem : InventoryData)
	{
		++Index;
		if (Elem.Value == Item)
			break;
	}

	InventoryData.Remove(Index);
}

UPPItemData* UPPInventoryComponent::GetActiveItem() const
{
	return *InventoryData.Find(ActiveItemIndex);
}
