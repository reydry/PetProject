// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPSpawnerManager.generated.h"

UCLASS()
class PETPROJECT_API APPSpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	

	APPSpawnerManager();

	UFUNCTION()
	virtual void Init();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInit();

protected:
	virtual void BeginPlay() override;

private:
	TSubclassOf<AActor> SpawnActorClass;
	
};
