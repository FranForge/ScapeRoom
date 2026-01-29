// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractionComponent.h"
#include "FPSCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionAvailability, bool, bAvailability);

UCLASS()
class SCAPEROOM_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

private:
/// <summary>
/// Clase que representa al personaje jugable en primera persona.
/// </summary>

public:
	AFPSCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookVerticalAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookHorizontalAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* RunAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractAction;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Look")
	UCameraComponent* FPSCamera;

	UPROPERTY(EditAnywhere, Category = "Look")
	float LookHorizontalSensitivity = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Look")
	float LookVerticalSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Look")
	float LookVerticalMinAngle = -89.0f;

	UPROPERTY(EditAnywhere, Category = "Look")
	float LookVerticalMaxAngle = 89.0f;


	UPROPERTY(EditAnywhere, Category = "Movement")
	float NormalSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RunningSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float StaminaConsumptionRate = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float StaminaRecoveryRate = 10.0f;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UInteractionComponent* InteractionComponent;


	/// <summary>
	/// Mueve al jugador hacia delante o hacia atras.
	/// </summary>
	/// <param name="Direction"></param>
	virtual void MoveForward(const FInputActionValue& Value);

	/// <summary>
	/// Mueve al jugador hacia la derecha o hacia la izquierda.
	/// </summary>
	/// <param name="Value"></param>
	virtual void MoveRight(const FInputActionValue& Value);

	/// <summary>
	/// Hace al jugador mirar en vertical rotando la camara unicamente.
	/// </summary>
	/// <param name="Value"></param>
	virtual void LookVertical(const FInputActionValue& Value);

	/// <summary>
	/// Hace al jugador mirar hacia izquierda y derecha rotando al jugador mismo.
	/// </summary>
	/// <param name="Value"></param>
	virtual void LookHorizontal(const FInputActionValue& Value);

	/// <summary>
	/// Energia que tiene actualmente el jugador, para poder correr.
	/// </summary>
	float Stamina;

	/// <summary>
	/// Indica si esta corriendo o no.
	/// </summary>
	bool bIsRunning;

	/// <summary>
	/// Consume energia si esta corriendo.
	/// </summary>
	/// <param name="DeltaTime"></param>
	virtual void ConsumeStamina(float DeltaTime);

	/// <summary>
	/// Recupera energia si no esta corriendo.
	/// </summary>
	/// <param name="DeltaTime"></param>
	virtual void RecoverStamina(float DeltaTime);

	/// <summary>
	/// Indica si el jugador puede correr o no.
	/// </summary>
	/// <returns></returns>
	virtual bool CanRun();

	/// <summary>
	/// Hace que el jugador comience a correr.
	/// </summary>
	virtual void StartRun();

	/// <summary>
	/// Hace que el jugador deje de correr.
	/// </summary>
	virtual void StopRun();

	/// <summary>
	/// Interactua usando el componente si puede.
	/// </summary>
	virtual void Interact();

public:	

	/// <summary>
	/// Evento que se lanza cuando cambia la disponibilidad de interaccion.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInteractionAvailability OnInteractionAvailabilityChanged;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
