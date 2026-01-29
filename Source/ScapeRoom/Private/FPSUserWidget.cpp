// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSUserWidget.h"

void UFPSUserWidget::DisplayInteractText(bool bDisplay)
{
	if (InteractText)
	{
		InteractText->SetVisibility(bDisplay ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}
