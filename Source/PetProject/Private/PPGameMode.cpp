// Fill out your copyright notice in the Description page of Project Settings.


#include "PPGameMode.h"
#include "GameModeComponents/PPSpawnerManager.h"

void APPGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;									

	if (IsValid(SpawnerComponentClass))
	{
		UWorld* World = GetWorld();
		if (IsValid(World))
		{
			SpawnerComponent = World->SpawnActor<APPSpawnerManager>(SpawnerComponentClass, SpawnInfo);
			SpawnerComponent->Init();
		}
	}

}
