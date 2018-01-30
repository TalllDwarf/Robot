// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotGun.h"

ARobotGun::ARobotGun(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	overheated = false;
	partHeat = 0.0f;
	heatRegenAmount = 2.0f;
	heatRegenTime = 0.6f;
}

//Cools the gun a little every tick
//Speed can be changed using heatRegenAmount and heatRegenTime
void ARobotGun::Cooldown(float DeltaTime)
{
	if (partHeat > 0.0f)
	{
		if (overheated)
		{
			partHeat = FMath::Clamp((partHeat - ((heatRegenAmount * 2) * DeltaTime)), 0.0f, 100.0f);
		}
		else
		{
			partHeat = FMath::Clamp((partHeat - (heatRegenAmount * DeltaTime)), 0.0f, 100.0f);
		}

			if (partHeat == 0.0f)
			{
				overheated = false;
			}
	}
}

//Checks if the gun can be used
bool ARobotGun::isActive()
{
	return (!overheated && !damaged);
}

//Add heat to the weapon
//overheating will stop the weapon 
void ARobotGun::AddHeat(float heat)
{
	partHeat = FMath::Clamp((partHeat + heat), 0.0f, 100.0f);

	if (partHeat == 100.0f)
	{
		overheated = true;
	}
}
