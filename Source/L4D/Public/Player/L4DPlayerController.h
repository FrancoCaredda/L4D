// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "L4DPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

struct FInputActionValue;

UCLASS()
class L4D_API AL4DPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void MoveTriggered(const FInputActionValue& Value);
	void LookTriggered(const FInputActionValue& Value);

	// TODO: Take a look at the PawnMovementComponent and how they prevent lags
	void FireStarted(const FInputActionValue& Value);
	void FireEnded(const FInputActionValue& Value);

	void JumpStarted(const FInputActionValue& Value);
	void JumpEnded(const FInputActionValue& Value);

	void FireTick();
protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> FireAction;
private:
	FTimerHandle FireTickTimer;
};
