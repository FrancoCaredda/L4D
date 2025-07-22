// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"


class AL4DWeaponBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquipped, AL4DWeaponBase*, Weapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class L4D_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	UFUNCTION(Server, Reliable)
	void EquipWeapon(AL4DWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable)
	bool TryShoot(const FVector& WorldPosition, const FVector& WorldDirection);

	UFUNCTION(BlueprintPure)
	float GetFireRate() const;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnWeaponEquipped WeaponEquipped;
protected:
	virtual void BeginPlay() override;

	bool Shoot(const FVector& WorldPosition, const FVector& WorldDirection);

	UFUNCTION(Server, Reliable)
	void AsyncShoot(const FVector& WorldPosition, const FVector& WorldDirection);

	UFUNCTION()
	void OnRep_EquippedWeapon();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AL4DWeaponBase> BaseWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float MaxShootingDistance;
	
	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	TObjectPtr<AL4DWeaponBase> EquippedWeapon;
};
