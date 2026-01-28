// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableTestActor.h"

// Sets default values
AInteractableTestActor::AInteractableTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableTestActor::Interact_Implementation(AActor* Caller)
{
	//Si no hay quien llame a esta interaccion, mostramos un error en el log.
	if (!Caller)
	{
		UE_LOG(LogTemp, Error, TEXT("No se ha encontrado quien llama a esta interaccion"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Interaccion realizada por: %s"), *Caller->GetName());
}

