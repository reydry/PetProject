// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PPGameMode.generated.h"

class APPSpawnerManager;

UCLASS()
class PETPROJECT_API APPGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void PreInitializeComponents() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	TSubclassOf<APPSpawnerManager> SpawnerComponentClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APPSpawnerManager> SpawnerComponent;
};
