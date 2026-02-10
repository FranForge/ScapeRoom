// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FItemStack.h"
#include "FInventory.generated.h"

/**
 * Define el inventario del nivel.
 */
USTRUCT(BlueprintType)
struct SCAPEROOM_API FInventory
{

	GENERATED_BODY()

public:
	FInventory();
	~FInventory();

	/// <summary>
	/// Lista de pilas de objetos que se encuentran en el inventario.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemStack> ItemStacks;

	/// <summary>
	/// Agrega un objeto al inventario o varios indicando la cantidad.
	/// </summary>
	/// <param name="ItemDef"></param>
	/// <param name="Quantity"></param>
	void AddItem(UItemDefinition* ItemDef, int32 Quantity);

	/// <summary>
	/// Agrega un solo objeto al inventario llamando a su sobrecarga.
	/// </summary>
	/// <param name="ItemDef"></param>
	void AddItem(UItemDefinition* ItemDef);

	/// <summary>
	/// Consulta cuanta cantidad de un objeto hay en el inventario sumando todas las pilas que contengan ese objeto.
	/// </summary>
	/// <param name="ItemDef"></param>
	/// <returns></returns>
	int32 GetItemQuantity(UItemDefinition* ItemDef) const;

	/// <summary>
	/// Elimina uno o varios objetos del mismo tipo del inventario y devuelve si se pudo eliminar la cantidad indicada.
	/// </summary>
	/// <param name="ItemDef"></param>
	/// <param name="Quantity"></param>
	/// <returns></returns>
	bool RemoveItem(UItemDefinition* ItemDef, int32 Quantity);

	/// <summary>
	/// Elimina un solo objeto del inventario llamando a su sobrecarga y devuelve si se pudo eliminar.
	/// </summary>
	/// <param name="ItemDef"></param>
	/// <returns></returns>
	bool RemoveItem(UItemDefinition* ItemDef);
};
