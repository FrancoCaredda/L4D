// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/HealthInterface.h"
#include "L4DPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class L4D_API AL4DPlayerState : public APlayerState, public IHealthInterface
{
	GENERATED_BODY()
public:
	AL4DPlayerState();

	virtual UHealthComponent* GetHealthComponent() const override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	TObjectPtr<UHealthComponent> HealthComponent;
};
