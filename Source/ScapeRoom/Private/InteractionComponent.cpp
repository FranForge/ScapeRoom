// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CanInteract();
}

bool UInteractionComponent::CanInteract()
{
	//Si no existe la camara, no se puede interactuar.
	if (!Camera)
	{
		CurrentInteractableActor = nullptr;
		return false;
	}

	//Lanza un Line Trace desde la camara hacia delante para ver si hay algo con lo que interactuar.
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * InteractionDistance);

	//Define los parametros de colision con el Line Trace.
	FHitResult Hit;
	FCollisionQueryParams Params;

	//Agrega la excepcion del actor propietario de este componente.
	Params.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

	//Si no ha colisionado con nada, no se puede interactuar.
	if (!bHit)
	{
		CurrentInteractableActor = nullptr;
		return false;
	}

	//Obtiene el actor con el que ha colisionado.
	AActor* HitActor = Hit.GetActor();

	//Si no hay actor colisionado no se puede interactuar.
	if (!HitActor)
	{
		CurrentInteractableActor = nullptr;
		return false;
	}

	//Si no implementa la interfaz de interactuable, no se puede interactuar.
	if (!HitActor->Implements<UInteractable>())
	{
		CurrentInteractableActor = nullptr;
		return false;
	}

	//Si ha llegado hasta aqui, se puede interactuar.
	UE_LOG(LogTemp, Log, TEXT("Puede interactuar con %s"), *HitActor->GetName());
	CurrentInteractableActor = HitActor;

	return true;
}

void UInteractionComponent::Interact()
{
	UE_LOG(LogTemp, Log, TEXT("Intentando interactuar."));

	//Si no puede interactuar no hace nada.
	if (!CanInteract()) return;

	UE_LOG(LogTemp, Log, TEXT("Interactuando con %s"), *CurrentInteractableActor->GetName());

	//Llama a la funcion de interaccion del actor interactuable y le pasa el actor propietario de este componente.
	IInteractable::Execute_Interact(CurrentInteractableActor, GetOwner());
}

