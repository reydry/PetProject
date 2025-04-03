// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonActivatableWidget.h"
#include "Components/ListView.h"
#include "PPGameSettingPanel.generated.h"

UCLASS()
class PETPROJECT_API UPPGameSettingPanel : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	UPPGameSettingPanel();

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

protected:

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UListView> ListView_Settings;
	
};
