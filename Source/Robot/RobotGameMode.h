// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "WaveClass.h"
#include "SpawnActor.h"
#include "GameFramework/GameModeBase.h"
#include "RobotGameMode.generated.h"

UCLASS(minimalapi)
class ARobotGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ARobotGameMode();
	UFUNCTION(BlueprintCallable)
		int getState();

	UFUNCTION(BlueprintCallable)
		void changeState(int newState);

	UFUNCTION(BlueprintCallable)
		void AddScore(int score);

	UFUNCTION(BlueprintCallable)
		int GetScore();

	UFUNCTION(BlueprintCallable)
		void SetEnemies(int amountOfEnemies);

	UFUNCTION(BlueprintCallable)
		int EnemiesLeft();

	UFUNCTION(BlueprintCallable)
		void KillEnemy();

private:
	int currentState;
	int totalScore;

	int numberOfEnemies;
};



