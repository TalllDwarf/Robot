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
	heatRegenAmount = 2.0f;
	heatRegenTime = 0.6f;
	
	const ConstructorHelpers::FObjectFinder<UCurveFloat> curve(TEXT("/Game/Test/GunActiveAnimationCurve"));
	check(curve.Succeeded());

	floatCurve = curve.Object;
	gunDisabledTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("GunActiveAnitmaionTimeline"));
	
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
				overheated = false;
				gunDisabledTimeLine->Reverse();
			}
	}
}

void ARobotGun::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineFloat callback{};
	callback.BindUFunction(this, FName{ TEXT("gunActiveTimelineCallback") });

	//Add the float curve to the timeline and connect to the timelines interpolation
	gunDisabledTimeLine->AddInterpFloat(floatCurve, callback, FName{ TEXT("gunActiveAnimation") });

	
	mainSpringArm = Cast<USpringArmComponent>(mainBody->GetComponentByClass(USpringArmComponent::StaticClass()));
}

void ARobotGun::gunActiveTimelineCallback(float value)
{
	float pitch = FMath::LerpStable(mainSpringArm->GetComponentRotation().Pitch, -80.0f, value);
	
	FRotator rotation = GetActorRotation();
	rotation.Pitch = pitch;
}

void ARobotGun::updateRotation()
{

	if (!gunDisabledTimeLine->IsPlaying())
	{
		FRotator rotation = GetActorRotation();
		rotation.Pitch = mainSpringArm->GetComponentRotation().Pitch;
	}
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
		gunDisabledTimeLine->Play();
	}
	else
	{
		gunDisabledTimeLine->Reverse();
	}
}

void ARobotGun::setDamaged(bool isDamaged)
{
	Super::setDamaged(isDamaged);

	if (isDamaged)
	{
		gunDisabledTimeLine->Play();
	}
	else
	{
		gunDisabledTimeLine->Reverse();
	}
}
