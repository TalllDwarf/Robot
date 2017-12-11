// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "Robot.h"
#include "RobotCharacter.h"
#include "Player/PlayerRobot.h"
#include "Player/RobotPart.h"
#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLY ECollisionChannel::ECC_GameTraceChannel3
// Sets default values
AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("ColComp"));
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
	
	health = 5;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(ARobotPart::StaticClass()))
	{
		Cast<ARobotPart>(OtherActor)->damage(50);
		takeDamage(health);
	}
}

void AEnemyCharacter::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		explode();
		Destroy();
	}
}

void AEnemyCharacter::explode_Implementation()
{
}


