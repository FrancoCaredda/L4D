// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/L4DHitScanWeapon.h"

AL4DHitScanWeapon::AL4DHitScanWeapon()
{
}

FVector AL4DHitScanWeapon::ShootInternal(const FVector& Point)
{
	FVector MuzzlePosition = GetMuzzle();

	FHitResult HitResult{};
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		MuzzlePosition,
		Point,
		ECollisionChannel::ECC_Visibility))
	{
		AActor* HitActor = HitResult.GetActor();
		ApplyDamage(HitActor, Damage);

		DrawDebugLine(GetWorld(), MuzzlePosition,
				Point, FColor::Green, false, 0.5f);

		return HitResult.ImpactPoint;
	}

	return FVector{};
}
