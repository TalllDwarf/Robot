// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "RobotGameMode.h"
#include "RobotCharacter.h"
#include "SpawnActor.h"
#include "UObject/ConstructorHelpers.h"
#include "UnrealEngine.h"

ARobotGameMode::ARobotGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Test/MyPlayerRobot"));

	currentState = 2;
	totalScore = 0;
	numberOfEnemies = 0;

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

int ARobotGameMode::getState()
{
	return currentState;
}

void ARobotGameMode::changeState(int newState)
{
	currentState = newState;
}

void ARobotGameMode::AddScore(int score)
{
	totalScore += score;
}

int ARobotGameMode::GetScore()
{
	return totalScore;
}

void ARobotGameMode::SetEnemies(int amountOfEnemies)
{
	numberOfEnemies = amountOfEnemies;
}

int ARobotGameMode::EnemiesLeft()
{
	return numberOfEnemies;
}

void ARobotGameMode::KillEnemy()
{
	numberOfEnemies--;
}
