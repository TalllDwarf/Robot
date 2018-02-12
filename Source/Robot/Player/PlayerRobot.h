// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerRobot.generated.h"

UCLASS()
class ROBOT_API APlayerRobot : public ACharacter
{
	GENERATED_BODY()

	//Head we have connected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class ARobotPart* headActor;

	//Arm actors we have connected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		TArray<class ARobotGun*> leftArms;

	//Arm actors we have connected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		TArray<class ARobotGun*> rightArms;

	//Leg we have connected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class ARobotLegPart* legActor;

public:
	// Sets default values for this character's properties
	APlayerRobot();

	//Turn rate deg/sec
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		float turnRate;

	//Stop the player from being able to strafe
	UFUNCTION(BlueprintCallable, Category = Movement)
		bool canStrafe();


	//Health of the robot
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
		float totalHealth;

	//Health of the robot
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
		float healthRemaining;

	//Damage the robot
	UFUNCTION(BlueprintCallable, Category = Health)
		void damage(float damage);

	//Heals the player
	UFUNCTION(BlueprintCallable, Category = Health)
		void heal(float healthAmount);

	//amount of health the parts will regen
	UPROPERTY(EditDefaultsOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float healthRegenAmount;

	//The time it takes to regen health
	UPROPERTY(EditDefaultsOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float healthRegenTime;

	//adds time for the player to heal themselves
	UFUNCTION(BlueprintCallable, Category = Health)
		void addHealTime(float healTime);

private:

	//The amount of healing time the part has
	float healingTime;

	//Until next health regen
	float healthRegenTimeLeft;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);

	void GamepadForward(float rate);

	void GamepadRight(float rate);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
