// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTTask_MoveToBack.h"
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

EBTNodeResult::Type UMyBTTask_MoveToBack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8*NodeMemory)
{

	AEnemyAI *CharPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	APlayerRobot *Enemy = Cast<APlayerRobot>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemykeyID));
	if (Enemy)
	{
		
		//CharPC->MoveToActor(Enemy, 0.0f, true, true, false, 0, true);
		FVector enemyLocation = Enemy->GetTargetLocation() + (Enemy->GetActorForwardVector() * -1500);
		if (CharPC->MoveToLocation(enemyLocation, 0.0f, true, true, false, true, 0, true))
		{
			CharPC->MoveToLocation(enemyLocation, 0.0f, true, true, false, true, 0, true);
		}
		else
		{
			APlayerRobot *Enemy = Cast<APlayerRobot>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemykeyID));
			CharPC->MoveToActor(Enemy, 0.0f, true, true, false, 0, true);
		}
		
		
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}


}



