// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SCAPEROOM_API UItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Nombre identificador del objeto.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemID;

	/// <summary>
	/// Nombre que se mostrara al jugador.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText DisplayName;

	/// <summary>
	/// Icono del objeto.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* Icon;

	/// <summary>
	/// Maximo de objetos que se pueden apilar en una sola ranura de inventario.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 MaxStackSize = 1;
	
};
