// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeComponents/PPSpawnerManager.h"

APPSpawnerManager::APPSpawnerManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APPSpawnerManager::Init()
{
	OnInit();
}

void APPSpawnerManager::BeginPlay()
{
	Super::BeginPlay();
}


