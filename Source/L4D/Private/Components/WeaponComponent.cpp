// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"

#include "Actors/L4DHitScanWeapon.h"
#include "Actors/L4DWeaponBase.h"
#include "Net/UnrealNetwork.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UWeaponComponent::Shoot(const FVector& WorldPosition, const FVector& WorldDirection)
{
	if (AL4DHitScanWeapon* HitScanWeapon = Cast<AL4DHitScanWeapon>(EquippedWeapon))
	{
		float ShootingDistance = HitScanWeapon->GetShootingDistance();
		FVector EndPosition = WorldPosition + WorldDirection * ShootingDistance;

		FHitResult Hit{};
		if (GetWorld()->LineTraceSingleByChannel(
			Hit,
			WorldPosition,
			EndPosition,
			ECollisionChannel::ECC_Visibility))
		{
			EquippedWeapon->Shoot(Hit.ImpactPoint + WorldDirection * 0.001);
			DrawDebugLine(GetWorld(), WorldPosition,
				WorldPosition + WorldDirection * 100000.0f, FColor::Red, false, 0.5f);
			return true;
		}

		return false;
	}

	return false;
	// TODO: Projectile shooting
}

void UWeaponComponent::AsyncShoot_Implementation(const FVector& WorldPosition, const FVector& WorldDirection)
{
	Shoot(WorldPosition, WorldDirection);
}

bool UWeaponComponent::TryShoot(const FVector& WorldPosition, const FVector& WorldDirection)
{
	if (Shoot(WorldPosition, WorldDirection))
	{
		AsyncShoot(WorldPosition, WorldDirection);
		return true;
	}

	return false;
}

float UWeaponComponent::GetFireRate() const
{
	if (EquippedWeapon)
	{
		return EquippedWeapon->GetFireRate();
	}

	return 0.0f;
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponComponent, EquippedWeapon);
}

void UWeaponComponent::EquipWeapon_Implementation(AL4DWeaponBase* Weapon)
{
	if (!Weapon)
	{
		return;
	}
	
	// TODO: Introduce an interface
	if (EquippedWeapon)
	{
		EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EquippedWeapon = nullptr;
	}

	EquippedWeapon = Weapon;
	EquippedWeapon->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	WeaponEquipped.Broadcast(EquippedWeapon);
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority && BaseWeaponClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = CastChecked<APawn>(GetOwner());
		SpawnParameters.Owner = GetOwner();
		
		EquippedWeapon = GetWorld()->SpawnActor<AL4DWeaponBase>(BaseWeaponClass, FTransform{}, SpawnParameters);
		EquippedWeapon->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		WeaponEquipped.Broadcast(EquippedWeapon);
	}
}

void UWeaponComponent::OnRep_EquippedWeapon()
{
	WeaponEquipped.Broadcast(EquippedWeapon);
}
