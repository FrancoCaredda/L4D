// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, CurrentHealth, float, MaxHealth, AActor*, Owner);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class L4D_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UHealthComponent();

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float Damage);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnHealthChanged HealthChanged;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_CurrentHealth();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth;
private:
	UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	float CurrentHealth;
};
