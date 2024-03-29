// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_MoveToBack.generated.h"

/**
 * 
 */
UCLASS()
class ROBOT_API UMyBTTask_MoveToBack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	


public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
	
};
