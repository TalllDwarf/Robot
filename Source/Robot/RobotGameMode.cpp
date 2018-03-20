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

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

int ARobotGameMode::getState()
{
	return currentState;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Gt State")));
}

void ARobotGameMode::changeState(int newState)
{
	currentState = newState;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Changed State")));
}

void ARobotGameMode::AddScore(int score)
{
	totalScore += score;
}

int ARobotGameMode::GetScore()
{
	return totalScore;
}
