// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "L4DWidgetController.generated.h"

class AL4DCharacter;

UCLASS(BlueprintType, Blueprintable)
class L4D_API UL4DWidgetController : public UObject
{
	GENERATED_BODY()
public:
	UL4DWidgetController();

	UFUNCTION(BlueprintCallable, Category = "Bindings")
	void SetPlayerState(APlayerState* NewPlayerState);

	UFUNCTION(BlueprintCallable, Category = "Bindings")
	void SetCharacter(AL4DCharacter* NewCharacter);
	
	UFUNCTION(BlueprintPure, Category = "Bindings")
	FORCEINLINE APlayerState* GetPlayerState() const { return PlayerState; }

	UFUNCTION(BlueprintPure, Category = "Bindings")
	FORCEINLINE AL4DCharacter* GetCharacter() const { return Character; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bindings")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bindings")
	TObjectPtr<AL4DCharacter> Character;
};
