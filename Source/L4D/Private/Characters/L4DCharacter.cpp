// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/L4DCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "Player/L4DPlayerState.h"

AL4DCharacter::AL4DCharacter()
{
	bUseControllerRotationYaw = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->bUsePawnControlRotation = true;
	
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	if (WeaponComponent)
	{
		WeaponComponent->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HandGrip_R"));
		WeaponComponent->SetIsReplicated(true);
	}
}

void AL4DCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	const AL4DPlayerState* pPlayerState = GetPlayerState<AL4DPlayerState>();
	check(pPlayerState);
	
	HealthComponent = pPlayerState->GetHealthComponent();
}

void AL4DCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	const AL4DPlayerState* pPlayerState = GetPlayerState<AL4DPlayerState>();
	check(pPlayerState);
	
	HealthComponent = pPlayerState->GetHealthComponent();
	HealthComponent->HealthChanged.AddDynamic(this, &AL4DCharacter::OnHealthChanged);
}

UHealthComponent* AL4DCharacter::GetHealthComponent() const
{
	return HealthComponent;
}

UWeaponComponent* AL4DCharacter::GetWeaponComponent() const
{
	return WeaponComponent;
}

void AL4DCharacter::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Health: %f"), CurrentHealth));
}
