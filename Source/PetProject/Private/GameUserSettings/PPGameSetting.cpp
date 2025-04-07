// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUserSettings/PPGameSetting.h"

void UPPGameSetting::SetName(FString InName)
{
	Name = InName;
}

void UPPGameSetting::SetDisplayName(FString InName)
{
	DisplayName = InName;
}

FString UPPGameSetting::GetName() const
{
	return Name;
}

FString UPPGameSetting::GetDisplayName()
{
	return DisplayName;
}

int32 UPPGameSetting::GetCurrentOption()
{
	int32 Option = GetCurrentOptionValue();

	return OptionValues[Option];
}

void UPPGameSetting::AddOption(int32 InValue, FText InOptiontText)
{
	OptionValues.Add(InValue);
	OptionDisplayTexts.Add(InOptiontText);
}

TArray<FText>& UPPGameSetting::GetOptionDisplayTexts()
{
	return OptionDisplayTexts;
}

void UPPGameSetting::AddGetter(TFunction<int32()> Func)
{
	Getter = Func;
}

void UPPGameSetting::AddSetter(TFunction<void(int32)> Func)
{
	Setter = Func;
}

void UPPGameSetting::SetValue(int32 Value)
{
	Setter(Value);
}

int32 UPPGameSetting::GetCurrentOptionValue() const
{
	return Getter();
}
