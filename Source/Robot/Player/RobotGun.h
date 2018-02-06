// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotPart.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RobotGun.generated.h"

/**
 * 
 */
UCLASS()
class ROBOT_API ARobotGun : public ARobotPart
{
	GENERATED_BODY()

		ARobotGun(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
public:

	UFUNCTION(BlueprintCallable, Category = Health)
	void Cooldown(float DeltaTime);

	//initiate on begin play
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:


private:

	//The current position of the gun
	//0 = faced up and ready 1 = down and damaged
	float damagedAnimationAlpha;

	//update the rotation to the rotation of the spring arm
	UFUNCTION(BlueprintCallable)
	void updateRotation();

	//
	//Gun kick back
	//

	//The amount the gun can kickback
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		float kickbackAmount;

	//Called when shooting to add kickback the gun
	UFUNCTION(BlueprintCallable, Category = Mesh)
		void Kickback();

	//
	//Heat
	//

	//is the gun currently overheated
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Heat, meta = (AllowPrivateAccess = "true"))
	bool overheated;

	//Returns the heat for the current part
	UFUNCTION(BlueprintPure, Category = Heat)
		float getPartHeat() { return partHeat; }

	//The heat of the part
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Heat, meta = (AllowPrivateAccess = "true"))
		float partHeat;

	//multiply the heat regen amount when the part has overheated
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Heat, meta = (AllowPrivateAccess = "true"))
		float overheatMultiplier;

	//amount of heat the parts will regen
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Heat, meta = (AllowPrivateAccess = "true"))
		float heatRegenAmount;

	//The time it takes to regen heat
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Heat, meta = (AllowPrivateAccess = "true"))
		float heatRegenTime;
	
	UFUNCTION(BlueprintCallable, Category = Heat)
		void AddHeat(float heat);

	//
	//End Heat
	//

	//If the part has been fully damaged or heated they are no longer active
	UFUNCTION(BlueprintCallable, Category = Health)
		virtual bool isActive() override;	
	
	//Is the gun overheating
	virtual void IsOverheating(bool overheating);

	//Spring arm of the camera
	USpringArmComponent* mainSpringArm;
	
	
};
