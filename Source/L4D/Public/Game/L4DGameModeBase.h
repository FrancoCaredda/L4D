// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "L4DGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerConnected, class AL4DPlayerState*, PlayerState);

UCLASS()
class L4D_API AL4DGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
public:
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnPlayerConnected OnPlayerConnected;
};
