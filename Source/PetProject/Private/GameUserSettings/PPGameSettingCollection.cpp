// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUserSettings/PPGameSettingCollection.h"

void UPPGameSettingCollection::AddSetting(UPPGameSetting* InSetting)
{
	SettingCollection.Add(InSetting);
}

TArray<UPPGameSetting*> UPPGameSettingCollection::GetSettingCollection()
{
	return SettingCollection;
}
