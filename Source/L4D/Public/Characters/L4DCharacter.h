// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/L4DCharacterBase.h"
#include "Interfaces/HealthInterface.h"
#include "Interfaces/WeaponInterface.h"
#include "L4DCharacter.generated.h"

class UWeaponComponent;
class USpringArmComponent;
class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerStateReplicated);

UCLASS()
class L4D_API AL4DCharacter : public AL4DCharacterBase, public IHealthInterface, public IWeaponInterface
{
	GENERATED_BODY()
public:
	AL4DCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual UHealthComponent* GetHealthComponent() const override;
	virtual UWeaponComponent* GetWeaponComponent() const override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateReplicated OnPlayerStateReplicated;
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UWeaponComponent> WeaponComponent;
};
