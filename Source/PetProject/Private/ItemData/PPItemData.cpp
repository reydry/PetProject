// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemData/PPItemData.h"
#include "Weapons/PPBaseWeapon.h"

FPrimaryAssetId UPPItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}

FString UPPItemData::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}
