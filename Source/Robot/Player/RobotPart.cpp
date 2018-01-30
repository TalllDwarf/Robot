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

	URobotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PartMesh"));

	RootComponent = URobotMesh;

	partHealth = maxPartHealth;

	setDamaged(false);
}

// Called when the game starts or when spawned
void ARobotPart::BeginPlay()
{
	Super::BeginPlay();
	
	mainBody = Cast<APlayerRobot>(GetOwner());
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

//Slowlt heals the part every tick
void ARobotPart::Heal(float DeltaTime)
{
	if (partHealth < maxPartHealth)
	{
		if (damaged)
		{
			partHealth = FMath::Clamp((partHealth + ((healthRegenAmount * 2) * DeltaTime)), 0.0f, maxPartHealth);
		}
		else
		{
			partHealth = FMath::Clamp((partHealth + (healthRegenAmount * DeltaTime)), 0.0f, maxPartHealth);
		}		

			if (partHealth == maxPartHealth)
			{
				setDamaged(false);
			}
	}
}