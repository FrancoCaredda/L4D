// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/L4DWeaponBase.h"
#include "L4DProjectileWeapon.generated.h"

class AL4DProjectileBase;

UCLASS()
class L4D_API AL4DProjectileWeapon : public AL4DWeaponBase
{
	GENERATED_BODY()
public:
	AL4DProjectileWeapon();
protected:
	virtual void BeginPlay() override;
	virtual FVector ShootInternal(const FVector& Point) override;
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AL4DProjectileBase> ProjectileClass;
};
