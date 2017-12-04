// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "RobotGameMode.h"
#include "RobotCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARobotGameMode::ARobotGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Test/MyPlayerRobot"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
