// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotPart.h"
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

	partHealth = 100.0f;
}

// Called when the game starts or when spawned
void ARobotPart::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARobotPart::damage(float damage)
{
	partHealth -= damage;
}

// Called every frame
void ARobotPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}