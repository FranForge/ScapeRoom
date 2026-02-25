// Fill out your copyright notice in the Description page of Project Settings.


#include "ScapeRoomGameMode.h"

AScapeRoomGameMode::AScapeRoomGameMode()
{
	//Establece el Game State de este Game Mode.
	GameStateClass = AScapeRoomGameState::StaticClass();
}