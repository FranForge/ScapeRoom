// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Agrega el contexto de mapeo de controles por defecto al subsistema de entrada moderno.
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	//Instancia la UI del jugador y la agrega al viewport.
	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if(HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void AFPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
