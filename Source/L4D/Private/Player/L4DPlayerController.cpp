// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/L4DPlayerController.h"

#include "Components/WeaponComponent.h"

#include "Interfaces/WeaponInterface.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

void AL4DPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem)
	{
		InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AL4DPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
		this, &AL4DPlayerController::MoveTriggered);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered,
		this, &AL4DPlayerController::LookTriggered);

	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started,
		this, &AL4DPlayerController::FireStarted);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed,
		this, &AL4DPlayerController::FireEnded);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started,
		this, &AL4DPlayerController::JumpStarted);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed,
		this, &AL4DPlayerController::JumpEnded);
}

void AL4DPlayerController::MoveTriggered(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();

	FRotator Rotation = GetControlRotation();
	FRotationMatrix RotationMatrix(FRotator{0.0f, Rotation.Yaw, 0.0f});

	FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
	FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);
	
	APawn* aPawn = GetPawn();
	aPawn->AddMovementInput(ForwardVector, Direction.Y);
	aPawn->AddMovementInput(RightVector, Direction.X);
}

void AL4DPlayerController::LookTriggered(const FInputActionValue& Value)
{
	FVector2D Rotation = Value.Get<FVector2D>();

	AddPitchInput(Rotation.Y);
	AddYawInput(Rotation.X);
}

void AL4DPlayerController::FireStarted(const FInputActionValue& Value)
{
	if (IWeaponInterface* WeaponInterface = Cast<IWeaponInterface>(GetPawn()))
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		UWeaponComponent* WeaponComponent = WeaponInterface->GetWeaponComponent();

		if (!TimerManager.IsTimerActive(FireTickTimer) ||
			!FireTickTimer.IsValid())
		{
			WeaponComponent->SetShootingState(true);
			FireTick();
			TimerManager.SetTimer(FireTickTimer, this, &AL4DPlayerController::FireTick,
				WeaponComponent->GetFireRate(), true);
		}
	}
}

void AL4DPlayerController::FireEnded(const FInputActionValue& Value)
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(FireTickTimer);

	if (IWeaponInterface* WeaponInterface = Cast<IWeaponInterface>(GetPawn()))
	{
		WeaponInterface->GetWeaponComponent()->SetShootingState(false);
	}
}

void AL4DPlayerController::JumpStarted(const FInputActionValue& Value)
{
	GetPawn<ACharacter>()->Jump();
}

void AL4DPlayerController::JumpEnded(const FInputActionValue& Value)
{
	GetPawn<ACharacter>()->StopJumping();
}

void AL4DPlayerController::FireTick()
{
	if (IWeaponInterface* WeaponInterface = Cast<IWeaponInterface>(GetPawn()))
	{
		int32 Width, Height;
		GetViewportSize(Width, Height);

		FVector WorldPosition, WorldDirection;
		if (DeprojectScreenPositionToWorld(Width * 0.5f, Height * 0.5f,
			WorldPosition, WorldDirection))
		{
			WeaponInterface->GetWeaponComponent()->TryShoot(WorldPosition, WorldDirection);
		}
	}
}
