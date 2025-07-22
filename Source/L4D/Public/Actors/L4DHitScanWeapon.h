// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/L4DWeaponBase.h"
#include "L4DHitScanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class L4D_API AL4DHitScanWeapon : public AL4DWeaponBase
{
	GENERATED_BODY()
public:
	AL4DHitScanWeapon();

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetShootingDistance() const { return ShootingDistance; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetDamage() const { return Damage; }
protected:
	virtual FVector ShootInternal(const FVector& Point) override;
protected:
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ShootingDistance;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float Damage;
};
