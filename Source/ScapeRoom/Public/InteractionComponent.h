// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Interactable.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAPEROOM_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Componente de camara que se usara para definir la direccion de interaccion.
	/// </summary>
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Interaction")
	UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionDistance = 200.0f;

	/// <summary>
	/// Indica si se puede interactuar o no con algo.
	/// </summary>
	/// <returns></returns>
	bool CanInteract();

	/// <summary>
	/// Actor con el que se puede interactuar actualmente.
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	AActor* CurrentInteractableActor = nullptr;

	/// <summary>
	/// Interactua con el objeto que pueda interactuar.
	/// </summary>
	void Interact();
};
