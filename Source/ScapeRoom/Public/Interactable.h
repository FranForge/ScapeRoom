// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/// <summary>
/// Clase interfaz que permite la interaccion con los objetos que la implementen.
/// </summary>
class SCAPEROOM_API IInteractable
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Interactua con el AActor y proporciona el AActor que ha interactuado con este.
	/// </summary>
	/// <param name="Caller"></param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Caller);

};
