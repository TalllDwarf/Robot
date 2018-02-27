// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_MoveToDrone.h"
#include "BTS_CheckForPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"
#include "RobotCharacter.h"
#include "GameplayTasks.h"
#include "Robot.h"
#include "Player/PlayerRobot.h"

EBTNodeResult::Type UMyBTTask_MoveToDrone::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyAI *CharPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());
	float floatx = FMath::RandRange(-700, 700);
	float floaty = FMath::RandRange(-700, 700);
	APlayerRobot *Enemy = Cast<APlayerRobot>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemykeyID));
	if (Enemy)
	{
		//CharPC->MoveToActor(Enemy, 0.0f, true, true, false, 0, true);
		FVector enemyLocation = FVector(Enemy->GetTargetLocation().X + floatx, Enemy->GetTargetLocation().Y + floaty, FMath::RandRange(1000, 3000));

		CharPC->MoveToLocation(enemyLocation, 0.0f, true, false, false, true, 0, true);

		if (FVector::Distance(enemyLocation, CharPC->GetTargetLocation()) < 1600)
		{
			return EBTNodeResult::Succeeded;
			
		}
		else
		{
			return EBTNodeResult::InProgress;
		}

		
	}
	else
	{
		return EBTNodeResult::Failed;
	}
	

}

