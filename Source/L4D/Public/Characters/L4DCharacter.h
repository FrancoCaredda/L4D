// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/L4DCharacterBase.h"
#include "L4DCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class L4D_API AL4DCharacter : public AL4DCharacterBase
{
	GENERATED_BODY()
public:
	AL4DCharacter();
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
};
