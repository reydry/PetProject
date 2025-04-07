// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "PPGameUserSettings.generated.h"

class UPPGameSettingCollection;
class UPPGameSetting;

UCLASS()
class PETPROJECT_API UPPGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public:
	UPPGameUserSettings();

	UFUNCTION(BlueprintCallable)
	static UPPGameUserSettings* Get();

	UPPGameSettingCollection* GetSettingCollection(FString& InSettingCollectionName);

protected:

private:
	void Initialize();

	UPPGameSettingCollection* InitializeVideoSettings();
	UPPGameSettingCollection* InitializeAudioSettings();
	
	UPROPERTY()
	TArray<UPPGameSettingCollection*> RegisteredSettings;
};
