// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPGameSetting.generated.h"

UCLASS(Blueprintable)
class PETPROJECT_API UPPGameSetting : public UObject
{
	GENERATED_BODY()
	
public:	
	void SetName(FString InName);
	void SetDisplayName(FString InName);
	
	FString GetName() const;
	FString GetDisplayName();
	int32 GetCurrentOption();

	void AddOption(int32 InValue, FText InOptiontText);

	TArray<FText>& GetOptionDisplayTexts();

	void AddGetter(TFunction<int32()> Func);
	void AddSetter(TFunction<void(int32)> Func);
	
	void SetValue(int32 Value);

protected:

	int32 GetCurrentOptionValue() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly)
	TArray<int32> OptionValues;

	UPROPERTY(BlueprintReadOnly)
	TArray<FText> OptionDisplayTexts;

	TFunction<int32()> Getter;
	TFunction<void(int32)> Setter;
};
