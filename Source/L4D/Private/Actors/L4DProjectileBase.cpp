// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/L4DProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Components/HealthComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Interfaces/HealthInterface.h"

AL4DProjectileBase::AL4DProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->AttachToComponent(SphereComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
}

void AL4DProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		SphereComponent->OnComponentHit.AddDynamic(this, &AL4DProjectileBase::OnProjectileHit);
	}
}

void AL4DProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IHealthInterface* HealthInterface = Cast<IHealthInterface>(OtherActor);

	if (HealthInterface)
	{
		UHealthComponent* HealthComponent = HealthInterface->GetHealthComponent();

		if (HealthComponent)
		{
			HealthComponent->TakeDamage(Damage);	
		}
	}
}


