// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotGun.h"
#include "Player/PlayerRobot.h"
#include "Engine.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

ARobotGun::ARobotGun(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	overheated = false;
	partHeat = 0.0f;
	overheatMultiplier = 3.0f;
	heatRegenAmount = 0.4f;
	heatRegenTime = 0.2f;	

	damagedAnimationAlpha = 0.0f;

}

//Cools the gun a little every tick
//Speed can be changed using heatRegenAmount and heatRegenTime
void ARobotGun::Cooldown(float DeltaTime)
{
	if (partHeat > 0.0f)
	{
		if (overheated)
		{
			partHeat = FMath::Clamp((partHeat - ((heatRegenAmount * overheatMultiplier) * DeltaTime)), 0.0f, 100.0f);
		}
		else
		{
			partHeat = FMath::Clamp((partHeat - (heatRegenAmount * DeltaTime)), 0.0f, 100.0f);
		}

		if (partHeat == 0.0f)
		{
			IsOverheating(false);
		}
	}
}

//Gets all the components 
void ARobotGun::BeginPlay()
{
	Super::BeginPlay();

	mainSpringArm = Cast<USpringArmComponent>(mainBody->GetComponentByClass(USpringArmComponent::StaticClass()));
}

//Used for the timeline tick
void ARobotGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Cooldown(DeltaTime);

	//damage animation
	if (isActive() && damagedAnimationAlpha != 0.0f)
	{
		damagedAnimationAlpha = FMath::Clamp((damagedAnimationAlpha - (DeltaTime * 2)), 0.0f, 1.0f);
	}
	else if (!isActive() && damagedAnimationAlpha != 1.0f)
	{
		damagedAnimationAlpha = FMath::Clamp((damagedAnimationAlpha + (DeltaTime * 2)), 0.0f, 1.0f);
	}

	updateRotation();
}


//Updates the guns rotation to look forward 
void ARobotGun::updateRotation()
{	
	FRotator rotation = GetActorRotation();
	rotation.Pitch = FMath::Lerp(mainSpringArm->GetComponentRotation().Pitch, -80.0f, damagedAnimationAlpha);
	SetActorRotation(rotation);
}

//Adds a small amount of kickback to the gun when shooting
void ARobotGun::Kickback()
{
}

//Checks if the gun can be used
bool ARobotGun::isActive()
{
	bool damaged = Super::isActive();
	return (!overheated && damaged);
}

//Add heat to the weapon
//overheating will stop the weapon 
void ARobotGun::AddHeat(float heat)
{
	partHeat = FMath::Clamp((partHeat + heat), 0.0f, 100.0f);

	if (partHeat == 100.0f)
	{
		IsOverheating(true);
	}
}

void ARobotGun::IsOverheating(bool overheating)
{
	overheated = overheating;
}
