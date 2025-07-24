// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/L4DUserWidget.h"

void UL4DUserWidget::SetController(UL4DWidgetController* NewController)
{
	WidgetController = NewController;
	OnControllerSet(WidgetController);
}
