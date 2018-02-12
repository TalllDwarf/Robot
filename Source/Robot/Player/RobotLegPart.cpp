// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotLegPart.h"

#include "Engine.h"

ARobotLegPart::ARobotLegPart(const FObjectInitializer& ObjectInitializer)
{
	canStrafe = true;
	selfRotate = false;
	ignoreGamepad = false;

	turnSpeed = 1.0f;
}

void ARobotLegPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARobotLegPart::MoveRight(float value)
{
	FRotator rotation(0, turnSpeed * value, 0);

	AddActorLocalRotation(rotation);
}

//Updates the movement from a gamepad
void ARobotLegPart::updateGamepadMovement(float x, float y, FRotator forward)
{
	if (x == 0 && y == 0)
	{
		ignoreGamepad = true;
	}
	else ignoreGamepad = false;

	if (!ignoreGamepad)
	{
		FVector aimToLocation(x, y, 0);
		SetActorRotation(forward + aimToLocation.Rotation());
	}
}