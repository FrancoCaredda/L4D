// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/L4DProjectileWeapon.h"
#include "Actors/L4DProjectileBase.h"

AL4DProjectileWeapon::AL4DProjectileWeapon()
{
}

void AL4DProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// TODO: Implement the projectile pool to reduce memory allocations
FVector AL4DProjectileWeapon::ShootInternal(const FVector& Point)
{
	FActorSpawnParameters SpawnParameters{};
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.Owner = this;

	FVector SpawnLocation = GetMuzzle() + FVector(1.0f, 0.0f, 1.0f) * 5.0f;
	
	GetWorld()->SpawnActor<AL4DProjectileBase>(ProjectileClass, SpawnLocation,
		GetActorRotation(), SpawnParameters);

	return FVector{};
}
