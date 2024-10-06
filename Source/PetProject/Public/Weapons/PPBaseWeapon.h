// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPBaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None = 0,
	Pistol = 1,
	Rifle = 2,
	Shotgun = 3,
	PlasmaRifle = 4,
	GaussCannon = 5,
	RocketLauncher = 6
};

UCLASS()
class PETPROJECT_API APPBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	APPBaseWeapon();

	virtual void Tick(float DeltaTime) override;

	EWeaponType GetWeaponType() const;

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMesh();

protected:
	virtual void BeginPlay() override;

	void InitWeapon();

	UPROPERTY(EditDefaultsOnly)
	EWeaponType WeaponType = EWeaponType::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};
