// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PPGameSettingPanel.h"
#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "GameUserSettings/PPGameUserSettings.h"
#include "GameUserSettings/PPGameSetting.h"
#include "GameUserSettings/PPSettingListEntry_Base.h"
#include "GameUserSettings/PPGameSettingCollection.h"

UPPGameSettingPanel::UPPGameSettingPanel()
{
	SetIsFocusable(true);
	bAutoActivate = true;
}

void UPPGameSettingPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UPPGameUserSettings* UserSettings = UPPGameUserSettings::Get();

	if (IsValid(UserSettings))
	{
		UserSettings->LoadSettings();

		GameSettingCollection = UserSettings->GetSettingCollection(CollectionName);
		
		if (GameSettingCollection)
		{
			for (UPPGameSetting* Setting : GameSettingCollection->GetSettingCollection())
			{
				ListView_Settings->AddItem(Setting);
			}
		}
	}
}

void UPPGameSettingPanel::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPPGameSettingPanel::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UPPGameSettingPanel::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	const UCommonInputSubsystem* InputSubsystem = GetInputSubsystem();

	if (InputSubsystem && InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad)
	{
		if (TSharedPtr<SWidget> PrimarySlateWidget = ListView_Settings->GetCachedWidget())
		{
			ListView_Settings->NavigateToIndex(0);
			ListView_Settings->SetSelectedIndex(0);

			FReply::Handled();
		}
	}

	return FReply::Unhandled();;
}

FString UPPGameSettingPanel::GetCollectionName()
{
	if (GameSettingCollection)
	{
		return GameSettingCollection->GetDisplayName();
	}

	return FString();
}
