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

	gunDisabledTimeLine = FTimeline{};
	
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

	//Callback for the timeline
	FOnTimelineFloat callback;
	callback.BindUFunction(this, FName( "gunActiveTimelineCallback"));

	//create a curve for the timeline getting to 1 in 0.5 seconds
	floatCurve = NewObject<UCurveFloat>();
	floatCurve->FloatCurve.AddKey(0.0f, 0.0f);
	floatCurve->FloatCurve.AddKey(0.5f, 1.0f);

	//Add the float curve to the timeline and connect to the timelines interpolation
	gunDisabledTimeLine.AddInterpFloat(floatCurve, callback);
	gunDisabledTimeLine.SetLooping(false);
	gunDisabledTimeLine.SetTimelineLength(0.5f);

	gunDisabledTimeLine.Reverse();

	mainSpringArm = Cast<USpringArmComponent>(mainBody->GetComponentByClass(USpringArmComponent::StaticClass()));
}

//Used for the timeline tick
void ARobotGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Cooldown(DeltaTime);

	updateRotation();

	gunDisabledTimeLine.TickTimeline(DeltaTime);
}

//makes the guns aim down when they have overheated or are damaged
void ARobotGun::gunActiveTimelineCallback(float value)
{
	//get the pitch we need
	float pitch = FMath::LerpStable(mainSpringArm->GetComponentRotation().Pitch, -80.0f, value);
	
	FRotator rotation = GetActorRotation();
	rotation.Pitch = pitch;

	SetActorRotation(rotation);
}

void ARobotGun::updateRotation()
{	
	if (gunDisabledTimeLine.GetPlaybackPosition() == 0.0f)
	{
		FRotator rotation = GetActorRotation();
		rotation.Pitch = mainSpringArm->GetComponentRotation().Pitch;
		SetActorRotation(rotation);
	}
	
}

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
		if (overheating)
		{
			gunDisabledTimeLine.Play();
		}
		else
		{
			gunDisabledTimeLine.Reverse();
		}
}

void ARobotGun::setDamaged(bool isDamaged)
{
	Super::setDamaged(isDamaged);

		if (isDamaged)
		{
			gunDisabledTimeLine.Play();
		}
		else
		{
			gunDisabledTimeLine.Reverse();
		}
}
