// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPInteractionComponent.generated.h"

class UPPAbilityInputConfig;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PETPROJECT_API UPPInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPInteractionComponent();

	UFUNCTION(BlueprintPure)
	TArray<AActor*> GetObjectsArray();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintPure)
	static UPPInteractionComponent* GetInteractionComponentFromActor(AActor* InActor);

protected:
	UPROPERTY(EditDefaultsOnly)
	UPPAbilityInputConfig* InputConfig;

private:
	UPROPERTY()
	TArray<AActor*> ObjectsArray;
};
