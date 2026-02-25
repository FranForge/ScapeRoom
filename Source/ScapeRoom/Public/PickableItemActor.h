// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ItemDefinition.h"
#include "ScapeRoomGameMode.h"
#include "PickableItemActor.generated.h"

UCLASS()
class SCAPEROOM_API APickableItemActor : public AActor, public IInteractable
{
	GENERATED_BODY()

protected:

	/// <summary>
	/// Tipo de objeto que dara al recoger este objeto.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UItemDefinition* ItemAsset;

	/// <summary>
	/// Cantidad de objetos que se daran al recoger este objeto.
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity = 1;

	/// <summary>
	/// Funcion que agregara el objeto al inventario del jugador que interactue con este objeto.
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Item")
	void PickUp();
	
public:	
	// Sets default values for this actor's properties
	APickableItemActor();

	virtual void Interact_Implementation(AActor* Caller) override;

};
