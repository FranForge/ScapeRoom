// Fill out your copyright notice in the Description page of Project Settings.


#include "FInventory.h"

FInventory::FInventory()
{
}

FInventory::~FInventory()
{
}

void FInventory::AddItem(UItemDefinition* ItemDef, int32 Quantity)
{
	//Si el elemento a agregar es nulo o la cantidad es menor o igual a 0, no se agrega nada.
	if (!ItemDef || Quantity <= 0) return;

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Agregando %d de %s (%s) al inventario"), 
										Quantity, *ItemDef->DisplayName.ToString(), *ItemDef->ItemID.ToString()));
	}

	//Obtiene la cantidad maxima que se puede agregar por stack para el item a agregar.
	int32 MaxStackSize = ItemDef->MaxStackSize;

	//Recorre todos las pilas de objetos buscando alguna con espacio libre para almacenar mas objetos del mismo tipo.
	for (int32 i = 0; i < ItemStacks.Num(); i++)
	{
		//Establece una referencia a la pila actual para facilitar su uso.
		FItemStack& Stack = ItemStacks[i];

		//Si la pila actual es de un tipo diferente no se hace nada.
		if (Stack.ItemDef != ItemDef) continue;

		//Si en la pila actual no hay espacio libre no se hace nada.
		if (Stack.Quantity >= MaxStackSize) continue;

		//Finalmente si hay espacio se agrega la cantidad maxima que se pueda a la pila.
		//Se calcula cuanto podria agregarse a la pila actual sin superar el maximo permitido.
		int32 SpaceLeft = MaxStackSize - Stack.Quantity;
		
		//Se calcula cuanto se agregara comparando el valor de cantidad indicado en el metodo.
		int32 ToAdd = FMath::Min(SpaceLeft, Quantity);

		//Se agrega la cantidad a la pila actual y se resta de la cantidad a agregar.
		Stack.Quantity += ToAdd;
		Quantity -= ToAdd;

		//Si ya no hay mas cantidad por agregar se termina el proceso.
		if (Quantity <= 0) return;
	}

	//Si queda cantidad tras buscar en todas las pilas existentes se crean nuevas pilas para almacenar el resto de objetos.
	while (Quantity > 0)
	{
		//Calcula cuanto puede agregar en una sola pila.
		int32 ToAdd = FMath::Min(MaxStackSize, Quantity);

		//Agrega una nueva pila al inventario con la cantidad calculada.
		ItemStacks.Add(FItemStack{ ItemDef, ToAdd });

		//Resta la cantidad agregada de la cantidad por agregar.
		Quantity -= ToAdd;
	}
}

void FInventory::AddItem(UItemDefinition* ItemDef)
{
	AddItem(ItemDef, 1);
}

int32 FInventory::GetItemQuantity(UItemDefinition* ItemDef) const
{
	//Crea una variable contador que almacenara la cantidad total de objetos del mismo tipo que hay en el inventario.
	int32 Quantity = 0;

	//Si el elemento a consultar es nulo se devuelve -1 indicando que no hay objetos de ese tipo en el inventario.
	if (!ItemDef) return -1;

	//Recorre todas las pilas para sumar la cantidad de objetos del mismo tipo.
	for (int32 i = 0; i < ItemStacks.Num(); i++)
	{
		//Crea una referencia a la pila actual para facilitar su uso.
		FItemStack Stack = ItemStacks[i];

		//Si la pila actual es de un tipo diferente no se hace nada.
		if (Stack.ItemDef != ItemDef) continue;

		//Si la pila actual es del mismo tipo se suma su cantidad a la cantidad total.
		Quantity += Stack.Quantity;
	}

	//Devuelve la cantidad total de objetos del mismo tipo que hay en el inventario.
	return Quantity;
}

bool FInventory::RemoveItem(UItemDefinition* ItemDef, int32 Quantity)
{
	//Si el elemento a eliminar es nulo o la cantidad es menor o igual a 0, no se elimina nada y se devuelve false.
	if (!ItemDef || Quantity <= 0) return false;

	//Recorre todas las pilas de objetos buscando alguna del mismo tipo para eliminar objetos en el orden inverso 
	//para que siempre se llenen las pilas y se reste de las ultimas.
	for (int32 i = ItemStacks.Num(); i >= 0; i--)
	{
		//Se define la referencia a la pila actual para facilitar su uso.
		FItemStack& Stack = ItemStacks[i];

		//Si la pila actual es de un tipo diferente no se hace nada.
		if (Stack.ItemDef != ItemDef) continue;

		//Si en la pila actual no hay objetos no se hace nada.
		if (Stack.Quantity <= 0) continue;

		//Calcula cuanto eliminara.
		int32 ToRemove = FMath::Min(Stack.Quantity, Quantity);

		//Elimina de la pila la cantidad maxima posible respetando la cantidad de la pila.
		Stack.Quantity -= ToRemove;

		//Si la pila queda vacia se elimina del inventario.
		if (Stack.Quantity <= 0) ItemStacks.RemoveAt(i);

		//Elimina de la cantidad a borrar lo que se ha eliminado.
		Quantity -= ToRemove;

		//Si no hay mas que eliminar se ha terminado el proceso de forma correcta.
		if (Quantity <= 0) return true;
	}

	//Si queda cantidad por eliminar se devuelve false indicando que no se pudo eliminar la cantidad indicada.
	if (Quantity > 0)
	{
		return false;
	}
	//Si se ha eliminado toda la cantidad se devuelve true indicando que se ha eliminado correctamente.
	else
	{
		return true;
	}
}

bool FInventory::RemoveItem(UItemDefinition* ItemDef)
{
	return RemoveItem(ItemDef, 1);
}
