// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PPAIController.h"

void APPAIController::PawnPendingDestroy(APawn* inPawn)
{
	if (ShouldDestroyAIControllerWithPlayerState)
	{
		CleanupPlayerState();
	}
	
	Super::PawnPendingDestroy(inPawn);
}
