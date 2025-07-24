// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeadMountedDisplayTypes.h"
#include "Blueprint/UserWidget.h"
#include "L4DUserWidget.generated.h"

class UL4DWidgetController;

UCLASS()
class L4D_API UL4DUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetController(UL4DWidgetController* NewController);

	UFUNCTION(BlueprintPure)
	FORCEINLINE UL4DWidgetController* GetController() const { return WidgetController; }

	UFUNCTION(BlueprintImplementableEvent)
	void OnControllerSet(UL4DWidgetController* Controller);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UL4DWidgetController> WidgetController;
};
