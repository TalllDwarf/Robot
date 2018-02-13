// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "MyBTTask_MoveToDrone.generated.h"

/**
 * 
 */
UCLASS()
class ROBOT_API UMyBTTask_MoveToDrone : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;



	
};
