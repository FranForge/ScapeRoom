// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSCharacter.generated.h"

UCLASS()
class SCAPEROOM_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookVerticalAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookHorizontalAction;

	UPROPERTY(EditAnywhere, Category = "Look")
	float LookSensitivity = 0.5f;


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

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
