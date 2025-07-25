// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/L4DGameModeBase.h"
#include "Player/L4DPlayerState.h"

void AL4DGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	OnPlayerConnected.Broadcast(NewPlayer->GetPlayerState<AL4DPlayerState>());
}
