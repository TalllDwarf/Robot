// Fill out your copyright notice in the Description page of Project Settings.

#include "ElevatorMovment.h"
#include "TimerManager.h"


// Sets default values
AElevatorMovment::AElevatorMovment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElevatorMovment::BeginPlay()
{

	for (int i = 0; i <= 10; i++)
	{
		FTimerHandle time_handler;
		GetWorldTimerManager().SetTimer(this,
			&AElevatorMovment::BeginPlay,
			true,
			12.0f);

		FVector ActorLocation = GetActorLocation();   // Get the current location 
		ActorLocation.Z += 50.0f;
		SetActorLocation(ActorLocation, true);    // Set the location 
	}

	Super::BeginPlay();

	
}

// Called every frame
void AElevatorMovment::Tick(float DeltaTime)
{
	

}


