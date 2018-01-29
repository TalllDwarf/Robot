// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreDrop.generated.h"

UCLASS()
class ROBOT_API AScoreDrop : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AScoreDrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Variables
	USphereComponent overlapSphere;
	
	
};
