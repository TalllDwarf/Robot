// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "RobotGameMode.h"
#include "RobotCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARobotGameMode::ARobotGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Test/MyPlayerRobot"));
	killCount = 0;
	currentState = 0;
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

int ARobotGameMode::getKills()
{
	return killCount;
}

int ARobotGameMode::getState()
{
	return currentState;
}

void ARobotGameMode::changeState(int newState)
{
	currentState = newState;
}

void ARobotGameMode::killedEnemy()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Hello")));
	killCount++;
	if (killCount > 25)
	{
		currentState = 1;
		UE_LOG(LogTemp, Warning, TEXT("Win"));
	}
}
