// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "L4DCharacterBase.generated.h"

UCLASS(Abstract)
class L4D_API AL4DCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AL4DCharacterBase();
protected:
	virtual void BeginPlay() override;
};
