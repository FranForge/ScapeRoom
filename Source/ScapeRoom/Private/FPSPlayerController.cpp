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
			//Muestra la UI en la pantalla.
			HUDWidget->AddToViewport();

			//Ahora intenta castear la UI a UFPSUserWidget para tener acceso a sus funciones personalizadas.
			FPSUserWidget = Cast<UFPSUserWidget>(HUDWidget);
		}
	}

	//Si el Pawn que esta poseyendo existe realiza ajustes adicionales.
	if (APawn* MyPawn = GetPawn())
	{
		//Intenta realizar ajustes si el Pawn poseido es FPSCharacter.
		if (AFPSCharacter* MyChar = Cast<AFPSCharacter>(MyPawn))
		{
			//Se suscribe a los delegados del personaje para actualizar la UI.
			MyChar->OnInteractionAvailabilityChanged.AddDynamic(FPSUserWidget, &UFPSUserWidget::DisplayInteractText);
		}
	}
}

void AFPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
