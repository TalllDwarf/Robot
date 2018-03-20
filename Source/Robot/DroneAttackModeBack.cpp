// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneAttackModeBack.h"
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
#include "Runtime/Core/Public/Math/UnrealMathUtility.h "
EBTNodeResult::Type UDroneAttackModeBack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyAI *CharPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());
	APlayerRobot *Enemy = Cast<APlayerRobot>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemykeyID));

	float floatx = FMath::RandRange(-3000,0);
	float floaty = FMath::RandRange(-3000, 0);
	float floatz = FMath::RandRange(1000, 2000);

	if (Enemy)
	{
		FVector EnemyLocation = Enemy->GetTargetLocation();

		CharPC->moveToPos = FVector(Enemy->GetTargetLocation().X + floatx, Enemy->GetTargetLocation().Y + floaty, Enemy->GetTargetLocation().Z + floatz);
		CharPC->MoveToLocation(CharPC->moveToPos, 100.0f, true, false, false, true, 0, true);

		return EBTNodeResult::Succeeded;

	}
	else
	{
		return EBTNodeResult::Failed;
	}
}





