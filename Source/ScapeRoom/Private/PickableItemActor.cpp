// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItemActor.h"

// Sets default values
APickableItemActor::APickableItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void APickableItemActor::PickUp()
{
	//Obtiene el GameState del mundo y llama a su funcion para agregar el item al inventario del jugador.
	AScapeRoomGameState* GS = GetWorld()->GetGameState<AScapeRoomGameState>();

	//Si no existe el GameState o no se ha asignado un ItemClass, no hace nada.
	if(!GS || !ItemAsset)
		return;

	//Agrega el item al inventario del jugador.
	GS->Inventory.AddItem(ItemAsset, Quantity);
}

void APickableItemActor::Interact_Implementation(AActor* Caller)
{
	PickUp();
	Destroy();
}

