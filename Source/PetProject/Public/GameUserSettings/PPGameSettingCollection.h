// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUserSettings/PPGameSetting.h"
#include "PPGameSettingCollection.generated.h"

/**
 * 
 */
UCLASS()
class PETPROJECT_API UPPGameSettingCollection : public UPPGameSetting
{
	GENERATED_BODY()
	
public:

	void AddSetting(UPPGameSetting* InSetting);

	TArray<UPPGameSetting*> GetSettingCollection();

protected:


private:
	UPROPERTY()
	TArray<UPPGameSetting*> SettingCollection;
	
};
