// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "RobotGameMode.h"
#include "RobotCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UnrealEngine.h"

ARobotGameMode::ARobotGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Test/MyPlayerRobot"));
	killCount = 0;
	currentState = 2;
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

int ARobotGameMode::getKills()
{
	return killCount;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Gt Kills")));
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

void ARobotGameMode::killedEnemy()
{
	
	killCount++;
	if (killCount >= 25)
	{
		currentState = 0;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("State 2")));
	}
}
