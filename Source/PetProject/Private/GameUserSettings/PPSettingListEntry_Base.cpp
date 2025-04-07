// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUserSettings/PPSettingListEntry_Base.h"
#include "GameUserSettings/PPGameSetting.h"
#include "CommonTextBlock.h"

void UPPSettingListEntry_Base::SetSetting(UPPGameSetting* InGameSetting)
{
	Setting = InGameSetting;
	
	UpdateText();
}

void UPPSettingListEntry_Base::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPPSettingListEntry_Base::UpdateText()
{
	Text_SettingName->SetText(FText::FromString(Setting->GetName()));
}

void UPPSettingListEntry_Discrete::UpdateText()
{
	Super::UpdateText();

	TArray<FText>& Texts = Setting->GetOptionDisplayTexts();
	RotatorSetting->PopulateTextLabels(Texts);
	RotatorSetting->SetSelectedItem(Setting->GetCurrentOption());
	//Setting->
}

void UPPSettingListEntry_Discrete::NativeOnInitialized()
{
	RotatorSetting->OnRotatedWithDirection.AddUniqueDynamic(this, &ThisClass::OnRotated);
}

void UPPSettingListEntry_Discrete::OnRotated(int32 Value, ERotatorDirection RotatorDir)
{
	Setting->SetValue(Value);
}
