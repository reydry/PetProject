// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/PPBaseWeapon.h"

APPBaseWeapon::APPBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
}

void APPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitWeapon();
}

void APPBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

EWeaponType APPBaseWeapon::GetWeaponType() const
{
	return WeaponType;
}

USkeletalMeshComponent* APPBaseWeapon::GetMesh()
{
	return SkeletalMeshComponent;
}

void APPBaseWeapon::InitWeapon()
{
}
