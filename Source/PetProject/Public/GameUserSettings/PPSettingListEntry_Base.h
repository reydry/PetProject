// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonRotator.h"
#include "PPSettingListEntry_Base.generated.h"

class UPPGameSetting;
class UCommonTextBlock;

UCLASS()
class PETPROJECT_API UPPSettingListEntry_Base : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	void SetSetting(UPPGameSetting* InGameSetting);

protected:

	virtual void NativeOnInitialized() override;

	virtual void UpdateText();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCommonTextBlock* Text_SettingName;

	UPROPERTY()
	UPPGameSetting* Setting;

private:
};

UCLASS()
class PETPROJECT_API UPPSettingListEntry_Discrete : public UPPSettingListEntry_Base
{
	GENERATED_BODY()

public:

	void UpdateText() override;

	void NativeOnInitialized() override;

	UFUNCTION()
	void OnRotated(int32 Value, ERotatorDirection RotatorDir);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonRotator* RotatorSetting;

private:

};
