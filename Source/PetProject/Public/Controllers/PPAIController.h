// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PPAIController.generated.h"

/**
 * 
 */
UCLASS()
class PETPROJECT_API APPAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void PawnPendingDestroy(APawn* inPawn);
	
	UPROPERTY(EditDefaultsOnly, meta = (Category = "Destroy"))
	bool ShouldDestroyAIControllerWithPlayerState = false;
};
