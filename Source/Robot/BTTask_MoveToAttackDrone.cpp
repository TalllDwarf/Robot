// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveToAttackDrone.h"
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

EBTNodeResult::Type UBTTask_MoveToAttackDrone::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	AEnemyAI *CharPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	APlayerRobot *Enemy = Cast<APlayerRobot>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemykeyID));



	float floatx = FMath::RandRange(-2000, 2000);

	float floaty = FMath::RandRange(-2000, 2000);



	

	

	if (Enemy)

	{

		FVector EnemyLocation = Enemy->GetTargetLocation();

		//CharPC->moveToPos = FVector(floatx, floaty, 2000);
		CharPC->moveToPos = FVector(Enemy->GetTargetLocation().X + floatx, Enemy->GetTargetLocation().Y + floaty, 1200);

		CharPC->MoveToLocation(CharPC->moveToPos, 100.0f, true, false, false, true, 0, true);



		if (FVector::Distance(CharPC->moveToPos, CharPC->GetTargetLocation()) < 4000)

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
