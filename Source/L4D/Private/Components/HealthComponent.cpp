// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::TakeDamage(float Damage)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MaxHealth);
		HealthChanged.Broadcast(CurrentHealth, MaxHealth);
	}
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::OnRep_CurrentHealth()
{
	HealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

