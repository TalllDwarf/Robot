// Fill out your copyright notice in the Description page of Project Settings.

#include "Rocket.h"


// Sets default values
ARocket::ARocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("rocketMesh"));

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	RootComponent = boxCollision;

	rocketMesh->SetupAttachment(RootComponent);
	rocketMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	speed = 100.0f;
	damage = 10.0f;
}

// Called when the game starts or when spawned
void ARocket::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (GetActorForwardVector() * speed));

	lifeTime -= DeltaTime;

	if (lifeTime <= 0.0f && !IsPendingKill())
	{
		Destroy();
	}
}
