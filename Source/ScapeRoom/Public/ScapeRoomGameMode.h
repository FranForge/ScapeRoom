// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ScapeRoomGameState.h"
#include "ScapeRoomGameMode.generated.h"

/**
 * Define el modo de juego y como se comportara el nivel del ScapeRoom.
 */
UCLASS()
class SCAPEROOM_API AScapeRoomGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AScapeRoomGameMode();
};
