// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class ROBOT_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(transient)
		class UBlackboardComponent *BlackboardComp;

	UPROPERTY(transient)
		class UBehaviorTreeComponent * BehaviorComp;

public:
	AEnemyAI();
	virtual void Possess(APawn * InPawn) override;

	uint8 EnemykeyID;
	
	FVector moveToPos = FVector(FMath::RandRange(-8000, 8000), FMath::RandRange(-8000, 8000), 2000);
	
};
