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

	//Do the legs rotate seporatly from the body
	UPROPERTY(EditDefaultsOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		bool legIsGyro;

	//The speed the legs rotate
	UPROPERTY(EditDefaultsOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		float turnSpeed;

	//Should we ignore gamepad input
	bool ignoreGamepad;

	//Gets the body start rotation so we can make our legs seperate
	FRotator startRotation;	

	//The speed the wheels should be turning, - meaning they are turning backwards
	bool wheelsTurning;
	bool playerMoving;

	//are we currently rotating;
	bool wheelsRotating;

public:
	ARobotLegPart(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//The speed the player moves when shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float walkLegSpeed;
	
	//The speed the player moves when they are not shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float runLegSpeed;

	UFUNCTION(BlueprintPure)
		bool ShouldWheelsSpin();

	UFUNCTION(BlueprintNativeEvent)
		void rightAxis(float value);
	virtual void rightAxis_Implementation(float value);

	UFUNCTION(BlueprintNativeEvent)
		void forwardAxis(float value);
	virtual void forwardAxis_Implementation(float value);

	bool isLegAGyro() { return legIsGyro; }

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Ticks each frame
	virtual void Tick(float DeltaTime) override;

	//returns if the legs can strafe or not
	bool canLegStrafe() { return canStrafe; }
	
	//returns if the legs will rotate alone from the body
	bool canLegsRotate() { return selfRotate; }

	virtual void MoveRight(float value);

	void ReverseParentRotation();

	void IsRotating(bool isThePlayerMoving) { wheelsTurning = isThePlayerMoving; };

	void IsMoving(bool isThePlayerMoving) { playerMoving = isThePlayerMoving; };

	void updateGamepadMovement(float x, float y, FRotator forward);
};
