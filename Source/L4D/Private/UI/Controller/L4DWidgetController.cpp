// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/L4DWidgetController.h"
#include "Characters/L4DCharacter.h"

UL4DWidgetController::UL4DWidgetController()
{
}

void UL4DWidgetController::SetPlayerState(APlayerState* NewPlayerState)
{
	PlayerState = NewPlayerState;
}

void UL4DWidgetController::SetCharacter(AL4DCharacter* NewCharacter)
{
	Character = NewCharacter;
}
