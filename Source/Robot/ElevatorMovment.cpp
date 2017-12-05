// Fill out your copyright notice in the Description page of Project Settings.

#include "ElevatorMovment.h"


// Sets default values
AElevatorMovment::AElevatorMovment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElevatorMovment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevatorMovment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

