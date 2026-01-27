// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSCharacter::MoveForward(const FInputActionValue& Value)
{
	//Obtiene el valor del eje de la accion.
	float AxisValue = Value.Get<float>();

	//Si existe un controlador y el valor del eje es diferente a 0, mueve el personaje.
	if (Controller && AxisValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

void AFPSCharacter::MoveRight(const FInputActionValue& Value)
{
	//Obtiene el valor del eje de la accion.
	float AxisValue = Value.Get<float>();

	//Si existe un controlador y el valor del eje es diferente a 0, mueve el personaje.
	if (Controller && AxisValue != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

void AFPSCharacter::LookVertical(const FInputActionValue& Value)
{
	
}

void AFPSCharacter::LookHorizontal(const FInputActionValue& Value)
{
	//Obtiene el valor del eje de la accion.
	float AxisValue = Value.Get<float>();

	//Rota al personaje en el eje Yaw.
	AddControllerYawInput(AxisValue * LookSensitivity);
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Castea a EnhancedInputComponent para usar Enhanced Input.
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AFPSCharacter::MoveForward);
		EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AFPSCharacter::MoveRight);
		EnhancedInput->BindAction(LookVerticalAction, ETriggerEvent::Triggered, this, &AFPSCharacter::LookVertical);
		EnhancedInput->BindAction(LookHorizontalAction, ETriggerEvent::Triggered, this, &AFPSCharacter::LookHorizontal);
	}

	//Registra el Mapping Context en el PlayerController.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

