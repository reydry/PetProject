// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonActivatableWidget.h"
#include "CommonListView.h"
#include "Components/ListView.h"
#include "PPGameSettingPanel.generated.h"

class UPPGameSettingCollection;

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

	UFUNCTION(BlueprintCallable)
	FString GetCollectionName();

protected:

	UPROPERTY(EditDefaultsOnly)
	FString CollectionName;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<UListView> ListView_Settings;
	
	UPROPERTY()
	UPPGameSettingCollection* GameSettingCollection;
};
