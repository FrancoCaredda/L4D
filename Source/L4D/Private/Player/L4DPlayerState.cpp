// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/L4DPlayerState.h"

#include "Components/HealthComponent.h"

AL4DPlayerState::AL4DPlayerState()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	if (HealthComponent)
	{
		HealthComponent->SetIsReplicated(true);
	}
}

UHealthComponent* AL4DPlayerState::GetHealthComponent() const
{
	return HealthComponent;
}
