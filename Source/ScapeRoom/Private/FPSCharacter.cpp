// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Busca el componente Camara entre los componentes del personaje.
	//Crea un array de las camaras que tiene el personaje.
	TArray<UCameraComponent*> Cameras;

	//Establece el array con todas las camaras que tiene el personaje.
	GetComponents<UCameraComponent>(Cameras);

	//Si hay al menos una camara, establece la primera como la camara del personaje.
	if (Cameras.Num() > 0)
	{
		FPSCamera = Cameras[0];
	}

	//Busca el componente de interaccion entre los componentes del personaje.
	InteractionComponent = FindComponentByClass<UInteractionComponent>();

	//Asigna la camara al componente de interaccion.
	if (InteractionComponent && FPSCamera)
	{
		InteractionComponent->Camera = FPSCamera;
	}

	//Establece la velocidad del personaje.
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
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
	float AxisValue = Value.Get<float>();

	//Si la camara no esta asignada no se hace nada.
	if (!FPSCamera) return;

	//Crea una nueva rotacion para la camara con respecto a la rotacion actual de esta.
	FRotator NewRotation = FPSCamera->GetRelativeRotation();

	//Limita la rotacion de la camara a unos limites.
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisValue * LookVerticalSensitivity, LookVerticalMinAngle, LookVerticalMaxAngle);

	//Aplica la rotacion a la camara.
	FPSCamera->SetRelativeRotation(NewRotation);
}

void AFPSCharacter::LookHorizontal(const FInputActionValue& Value)
{
	//Obtiene el valor del eje de la accion.
	float AxisValue = Value.Get<float>();

	//Rota al personaje en el eje Yaw.
	AddControllerYawInput(AxisValue * LookHorizontalSensitivity);
}

void AFPSCharacter::ConsumeStamina(float DeltaTime)
{
	//Resta la energia y la limita.
	Stamina -= StaminaConsumptionRate * DeltaTime;
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

void AFPSCharacter::RecoverStamina(float DeltaTime)
{
	//Suma la energia y la limita.
	Stamina += StaminaRecoveryRate * DeltaTime;
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

bool AFPSCharacter::CanRun()
{
	//Puede correr si tiene energia.
	return Stamina > 0.0f;
}

void AFPSCharacter::StartRun()
{
	//Si no puede correr, no hace nada.
	if (!CanRun()) return;

	//Establece la velocidad de carrera.
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	bIsRunning = true;
}

void AFPSCharacter::StopRun()
{
	//Establece la velocidad normal.
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	bIsRunning = false;
}

void AFPSCharacter::Interact()
{
	//Si el componente de interaccion esta asignado, llama a su metodo Interact.
	if (InteractionComponent)
	{
		InteractionComponent->Interact();
	}
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Si esta corriendo consume energia, si no, la recupera.
	if (bIsRunning)
	{
		ConsumeStamina(DeltaTime);

		//Si ya no puede correr, lo detiene.
		if (!CanRun()) StopRun();
	}
	else
	{
		RecoverStamina(DeltaTime);
	}
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
		EnhancedInput->BindAction(RunAction, ETriggerEvent::Started, this, &AFPSCharacter::StartRun);
		EnhancedInput->BindAction(RunAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopRun);
		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AFPSCharacter::Interact);
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

