// Fill out your copyright notice in the Description page of Project Settings.

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


UBTS_CheckForPlayer::UBTS_CheckForPlayer()
{
	bCreateNodeInstance = true;
}
void UBTS_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8*NodeMemory, float DeltaSeconds)
{
	AEnemyAI* EnemyPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (EnemyPC)
	{
		ARobotCharacter *Enemy = Cast<ARobotCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->EnemykeyID, Enemy);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Enemy Is Here!");
		}
	}
	
}

