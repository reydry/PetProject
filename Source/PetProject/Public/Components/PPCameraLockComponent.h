// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPCameraLockComponent.generated.h"

class APPCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PETPROJECT_API UPPCameraLockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPCameraLockComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* InTarget);
	
	UFUNCTION(BlueprintCallable)
	void SetLockOnTarget(bool InLockOnTarget);

	UFUNCTION(BlueprintPure)
	AActor* GetTarget() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void TargetLost();

	void CheckDistanceToTarget();

private:
	void SubscribeToDelegates();
	void UnSubscribeFromDelegates();

	void UpdateCameraRotation();
	void InitComponents();
	
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	APawn* Owner;

	UPROPERTY()
	APPCharacter* Target;

	bool bLockOnTarget = false;

	UPROPERTY(EditDefaultsOnly)
	double DistanceThreshold = 1000;
};
