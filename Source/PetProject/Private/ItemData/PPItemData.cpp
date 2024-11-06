// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemData/PPItemData.h"

bool UPPItem::IsConsumable() const
{
	return ItemType == EItemType::Consumable;
}

bool UPPItem::IsWeapon() const
{
	return ItemType == EItemType::Weapon;
}

bool UPPItem::IsSpell() const
{
	return ItemType == EItemType::Spell;
}
