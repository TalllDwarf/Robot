// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/RobotPart.h"
#include "RobotLegPart.generated.h"

/**
 * 
 */
UCLASS()
class ROBOT_API ARobotLegPart : public ARobotPart
{
	GENERATED_BODY()

	//Can the legs strafe
	UPROPERTY(EditDefaultsOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool canStrafe;

	//Do the legs rotate seporatly from the body
	UPROPERTY(EditDefaultsOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool selfRotate;

	//The speed the legs rotate
	UPROPERTY(EditDefaultsOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float turnSpeed;

	//Should we ignore gamepad input
	bool ignoreGamepad;

public:
	ARobotLegPart(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	//Ticks each frame
	void Tick(float DeltaTime) override;

	//returns if the legs can strafe or not
	bool canLegStrafe() { return canStrafe; }
	
	//returns if the legs will rotate alone from the body
	bool canLegsRotate() { return selfRotate; }

	virtual void MoveRight(float value);

	void updateGamepadMovement(float x, float y, FRotator forward);
};
