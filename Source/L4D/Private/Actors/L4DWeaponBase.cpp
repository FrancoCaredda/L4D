// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/L4DWeaponBase.h"
#include "Interfaces/HealthInterface.h"
#include "Components/HealthComponent.h"

AL4DWeaponBase::AL4DWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(SkeletalMeshComponent);

	Muzzle = CreateDefaultSubobject<USceneComponent>("Muzzle");
	Muzzle->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SetReplicates(true);
}

void AL4DWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AL4DWeaponBase::ApplyDamage(AActor* TargetActor, float Damage) const
{
	IHealthInterface* HealthInterface = Cast<IHealthInterface>(TargetActor);

	if (HealthInterface)
	{
		UHealthComponent* HealthComponent = HealthInterface->GetHealthComponent();

		if (HealthComponent)
		{
			HealthComponent->TakeDamage(Damage);	
		}
	}
}

