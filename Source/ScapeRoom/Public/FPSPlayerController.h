// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SCAPEROOM_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/// <summary>
	/// Mapa de controles por defecto.
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	/// <summary>
	/// Clase de la UI del jugador.
	/// </summary>
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	/// <summary>
	/// Instancia de la UI del jugador.
	/// </summary>
	UUserWidget* HUDWidget;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

};
