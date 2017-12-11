// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotGun.h"

ARobotGun::ARobotGun(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	overheated = false;
	partHeat = 0.0f;
	heatRegenAmount = 2.0f;
	heatRegenTime = 0.6f;
	heatRegenTimeLeft = heatRegenTime;
}

void ARobotGun::Cooldown(float DeltaTime)
{
	if (partHeat > 0.0f)
	{
			partHeat = FMath::Clamp((partHeat - (heatRegenAmount * DeltaTime)), 0.0f, 100.0f);
			heatRegenTimeLeft = heatRegenTime;

			if (partHeat == 0.0f)
			{
				overheated = false;
			}
	}
}

bool ARobotGun::isActive()
{
	return (!overheated && !damaged);
}

void ARobotGun::AddHeat(float heat)
{
	partHeat = FMath::Clamp((partHeat + heat), 0.0f, 100.0f);

	if (partHeat == 100.0f)
	{
		overheated = true;
	}
}
