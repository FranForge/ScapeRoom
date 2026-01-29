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
}

void AFPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
