#include "RobotLegPart.h"
#include "Engine.h"

ARobotLegPart::ARobotLegPart(const FObjectInitializer& ObjectInitializer)
{
	canStrafe = true;
	selfRotate = false;
	ignoreGamepad = false;

	turnSpeed = 1.5f;	

	wheelsTurning = false;
}

bool ARobotLegPart::ShouldWheelsSpin()
{
	return (wheelsTurning || wheelsRotating || playerMoving);
}

void ARobotLegPart::rightAxis_Implementation(float value)
{
}

void ARobotLegPart::forwardAxis_Implementation(float value)
{
}

void ARobotLegPart::BeginPlay()
{
	Super::BeginPlay();
	startRotation = mainBody->GetActorRotation();
}

void ARobotLegPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARobotLegPart::MoveRight(float value)
{
	FRotator rotation(0, turnSpeed * value, 0);
	SetActorRotation(GetActorRotation() + rotation);
}

void ARobotLegPart::ReverseParentRotation()
{
	SetActorRotation(GetActorRotation() - (mainBody->GetActorRotation() - startRotation));
	startRotation = mainBody->GetActorRotation();
}

//Updates the movement from a gamepad
void ARobotLegPart::updateGamepadMovement(float x, float y, FRotator forward)
{
	if (x == 0 && y == 0)
	{
		ignoreGamepad = true;
	}
	else
	{
		ignoreGamepad = false;

	}

	if (!ignoreGamepad)
	{
		FVector aimToLocation(x, y, 0);
		aimToLocation.Normalize();
		FRotator rotation = aimToLocation.Rotation();
		SetActorRotation(forward + rotation);		

		if (x != 0 || y != 0)
		{
			wheelsRotating = true;
		}
		else wheelsRotating = false;
	}

}