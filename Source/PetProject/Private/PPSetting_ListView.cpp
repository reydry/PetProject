// Fill out your copyright notice in the Description page of Project Settings.


#include "PPSetting_ListView.h"
#include "GameUserSettings/PPGameSetting.h"
#include "GameUserSettings/PPSettingListEntry_Base.h" 

UPPSetting_ListView::UPPSetting_ListView(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UUserWidget& UPPSetting_ListView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryWidgetClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	UPPGameSetting* SettingItem = Cast<UPPGameSetting>(Item);

	TSubclassOf<UPPSettingListEntry_Base> SettingEntryClass = TSubclassOf<UPPSettingListEntry_Base>(DesiredEntryWidgetClass);
	UPPSettingListEntry_Base& EntryWidget = GenerateTypedEntry<UPPSettingListEntry_Base>(SettingEntryClass, OwnerTable);

	if (!IsDesignTime())
	{
		EntryWidget.SetSetting(SettingItem);
	}

	return EntryWidget;
}
