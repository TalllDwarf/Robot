// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_CheckForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ROBOT_API UBTS_CheckForPlayer : public UBTService
{
	GENERATED_BODY()

public:
	
	UBTS_CheckForPlayer();
	
	virtual void TickNode(UBehaviorTreeComponent& ownercomp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
	
};
