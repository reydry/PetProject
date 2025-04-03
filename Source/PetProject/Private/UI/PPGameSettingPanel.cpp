// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PPGameSettingPanel.h"
#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"

UPPGameSettingPanel::UPPGameSettingPanel()
{
	SetIsFocusable(true);
	bAutoActivate = true;
}

void UPPGameSettingPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
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
