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

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//The timeline to rotate the gun when it is disabled
	UTimelineComponent* gunDisabledTimeLine;

	//animation alpha curve
	UCurveFloat* floatCurve;

	//Timeline tick call
	void gunActiveTimelineCallback(float value);

	//update the rotation to the rotation of the spring arm
	UFUNCTION(BlueprintCallable)
	void updateRotation();

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
	
	//If the part has been fully damaged or heated they are no longer active
	UFUNCTION(BlueprintCallable, Category = Health)
		virtual bool isActive() override;

	UFUNCTION(BlueprintCallable, Category = Heat)
		void AddHeat(float heat);
	
	//Is the gun overheating
	virtual void IsOverheating(bool overheating);

	//Override set damage of robot part
	// used to start gun animations
	virtual void setDamaged(bool isDamaged) override;

	//Spring arm of the camera
	USpringArmComponent* mainSpringArm;
	
	
};
