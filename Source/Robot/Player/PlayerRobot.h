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
		class ARobotPart* legActor;

public:
	// Sets default values for this character's properties
	APlayerRobot();

	//Turn rate deg/sec
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		float turnRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
