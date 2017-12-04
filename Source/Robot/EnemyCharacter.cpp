// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "Robot.h"
#include "RobotCharacter.h"
#define COLLISION_ENEMY ECollisionChannel::ECC_GameTraceChannel2
#define COLLISION_ALLY ECollisionChannel::ECC_GameTraceChannel3
// Sets default values
AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ColComp"));
	

	CollisionComp->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnHit);

	CollisionComp->BodyInstance.SetCollisionProfileName("enemy");
	CollisionComp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
	
	CollisionComp->SetCollisionObjectType(COLLISION_ENEMY);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ENEMY, ECollisionResponse::ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(COLLISION_ALLY, ECollisionResponse::ECR_Block);

	GetCapsuleComponent()->AttachToComponent(CollisionComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

//	RootComponent = CollisionComp;

	

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

void AEnemyCharacter::OnHit(class UPrimitiveComponent* HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->IsA(ARobotCharacter::StaticClass()))
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Touch");
		takeDamage(health);
	}
}

void AEnemyCharacter::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		Destroy();
	}
}

