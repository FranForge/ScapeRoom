// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefinition.h"
#include "FItemStack.generated.h"

/**
 * Declara una pila de items en el inventario.
 */
USTRUCT(BlueprintType)
struct SCAPEROOM_API FItemStack
{

	GENERATED_BODY()

public:

	//Constructor.
	FItemStack();

	/// <summary>
	/// Constructor con parametros.
	/// </summary>
	/// <param name="ItemDef"></param>
	/// <param name="Quantity"></param>
	FItemStack(UItemDefinition* ItemDef, int32 Quantity);

	//Destructor.
	~FItemStack();

	/// <summary>
	/// Objeto que se encuentra en la pila.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemDefinition* ItemDef;

	/// <summary>
	/// Cantidad de objetos en la pila.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;
};
