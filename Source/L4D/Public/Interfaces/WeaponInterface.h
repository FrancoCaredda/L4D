// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"

class UWeaponComponent;

UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class L4D_API IWeaponInterface
{
	GENERATED_BODY()
public:
	virtual UWeaponComponent* GetWeaponComponent() const = 0;
};
