// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RobotGameMode.generated.h"

UCLASS(minimalapi)
class ARobotGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARobotGameMode();
	UFUNCTION(BlueprintCallable)
		int getKills();
	UFUNCTION(BlueprintCallable)
		int getState();
	UFUNCTION(BlueprintCallable)
		void changeState(int newState);
	UFUNCTION(BlueprintCallable)
		void killedEnemy();
private:
	int currentState;
	int killCount;
};



