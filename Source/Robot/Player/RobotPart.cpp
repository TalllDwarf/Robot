// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
#include "Math/UnrealMathUtility.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ARobotPart::ARobotPart(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	URobotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PartMesh"));
	//UboxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));

	RootComponent = URobotMesh;
	//UboxCollider->SetupAttachment(RootComponent);

	partHealth = maxPartHealth;

	damaged = false;
}

// Called when the game starts or when spawned
void ARobotPart::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARobotPart::damage(float damage)
{
	partHealth = FMath::Clamp((partHealth - damage), 0.0f, maxPartHealth);
	if (partHealth <= 0)
	{
		Destroy();
	}
}

void ARobotPart::addHealth(float healthAmount)
{
	partHealth = FMath::Clamp((partHealth + healthAmount), 0.0f, maxPartHealth);
}

bool ARobotPart::isActive()
{
	return !damaged;
}

void ARobotPart::Heal(float DeltaTime)
{
	if (partHealth < maxPartHealth)
	{
		//	partHealth = FMath::Clamp((partHealth + (healthRegenAmount * DeltaTime)), 0.0f, maxPartHealth);
			healthRegenTimeLeft = healthRegenTime;

			if (partHealth == maxPartHealth)
			{
				damaged = false;
			}
	}

}