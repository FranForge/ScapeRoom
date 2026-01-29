// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "FPSUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCAPEROOM_API UFPSUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/// <summary>
	/// Texto que se mostrara cuando el jugador pueda interactuar con un objeto.
	/// </summary>
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractText;

	/// <summary>
	/// Muestra o no el texto de interaccion.
	/// </summary>
	/// <param name="bDisplay"></param>
	void DisplayInteractText(bool bDisplay);

};
