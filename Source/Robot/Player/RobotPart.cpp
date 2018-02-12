// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "Math/UnrealMathUtility.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Robot/Player/PlayerRobot.h"

// Sets default values
ARobotPart::ARobotPart(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	maxPartHealth = 100.0f;
	partHealth = 100.0f;
	healingMultiplier = 2.0f;

	URobotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PartMesh"));
	RootComponent = URobotMesh;

	setDamaged(false);
}

// Called when the game starts or when spawned
void ARobotPart::BeginPlay()
{
	Super::BeginPlay();
	
	mainBody = Cast<APlayerRobot>(GetOwner());
}

void ARobotPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARobotPart::setDamaged(bool isDamaged)
{
	damaged = isDamaged;
}

//Damage the robot part
void ARobotPart::damage(float damage)
{
	//Damage part
	partHealth = FMath::Clamp((partHealth - damage), 0.0f, maxPartHealth);
	if (partHealth <= 0)
	{
		setDamaged(true);
	}

	//Damge main body
	mainBody->damage(damage);
}

//Heals the robot part
void ARobotPart::addHealth(float healthAmount)
{
	partHealth = FMath::Clamp((partHealth + healthAmount), 0.0f, maxPartHealth);
	if (partHealth == maxPartHealth)
	{
		setDamaged(false);
	}
}

//Is the part currently active
bool ARobotPart::isActive()
{
	return !damaged;
}