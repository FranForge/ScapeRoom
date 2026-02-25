// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FInventory.h"
#include "ScapeRoomGameState.generated.h"

/**
 * 
 */
UCLASS()
class SCAPEROOM_API AScapeRoomGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FInventory Inventory;
};
