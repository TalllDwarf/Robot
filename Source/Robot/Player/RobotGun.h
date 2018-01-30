// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotPart.h"
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

private:

	//is the gun currently overheated
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	bool overheated;

	UFUNCTION(BlueprintPure, Category = Health)
		float getPartHeat() { return partHeat; }

	//The heat of the part
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
		float partHeat;

	//amount of heat the parts will regen
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float heatRegenAmount;

	//The time it takes to regen heat
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float heatRegenTime;
	
	//If the part has been fully damaged or heated they are no longer active
	UFUNCTION(BlueprintCallable, Category = Health)
		virtual bool isActive() override;

	UFUNCTION(BlueprintCallable, Category = Health)
		void AddHeat(float heat);
	
};
