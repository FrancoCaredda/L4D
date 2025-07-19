// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

class UHealthComponent;

UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};


class L4D_API IHealthInterface
{
	GENERATED_BODY()
public:
	virtual UHealthComponent* GetHealthComponent() const = 0;
};
