// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/L4DCharacter.h"
#include "Camera/CameraComponent.h"

AL4DCharacter::AL4DCharacter()
{
	bUseControllerRotationYaw = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->bUsePawnControlRotation = true;
}
