// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneAttackMode.h"
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

EBTNodeResult::Type UDroneAttackMode::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	AEnemyAI *CharPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());
	APlayerRobot *Enemy = Cast<APlayerRobot>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemykeyID));
	const FVector EnemyLocation = Enemy->GetTargetLocation();

	CharPC->MoveToLocation(FVector(FMath::RandRange(8500, -8500), FMath::RandRange(8500, -8500), 2000));
		
	return EBTNodeResult::Type();
}
