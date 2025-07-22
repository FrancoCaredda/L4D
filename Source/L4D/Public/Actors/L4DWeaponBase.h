// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "L4DWeaponBase.generated.h"

UCLASS(Abstract)
class L4D_API AL4DWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AL4DWeaponBase();

	UFUNCTION(BlueprintNativeEvent)
	void Shoot(const FVector& Point);
	void Shoot_Implementation(const FVector& Point)
	{
		FVector HitPoint = ShootInternal(Point);
		ApplyHitImpact(HitPoint);
	}
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE FVector GetMuzzle() const { return Muzzle->GetComponentLocation(); }

	UFUNCTION(BlueprintPure)
	FORCEINLINE int GetMaxAmmoAmount() const { return MaxAmmoAmount; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetFireRate() const { return FireRate; }
protected:
	virtual void BeginPlay() override;
	
	virtual FVector ShootInternal(const FVector& Point)
	{  static_assert("The AL4DWeaponBase::ShootInternal has to be overridden "); return FVector{}; }

	UFUNCTION(BlueprintImplementableEvent)
	void ApplyHitImpact(const FVector& HitPoint);
	
	void ApplyDamage(AActor* TargetActor, float Damage) const;
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> Muzzle;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int MaxAmmoAmount;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float FireRate;
};
