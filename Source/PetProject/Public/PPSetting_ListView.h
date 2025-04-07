// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "PPSetting_ListView.generated.h"

UCLASS()
class PETPROJECT_API UPPSetting_ListView : public UListView
{
	GENERATED_BODY()
	
public:
	UPPSetting_ListView(const FObjectInitializer& ObjectInitializer);

protected:

	UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;

private:
	
	
};
