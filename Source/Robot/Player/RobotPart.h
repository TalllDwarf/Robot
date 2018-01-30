// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobotPart.generated.h"

UCLASS()
class ROBOT_API ARobotPart : public AActor
{
	GENERATED_BODY()

	//Head we have connected
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* URobotMesh;
	
public:	
	// Sets default values for this actor's properties
	ARobotPart(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return URobotMesh; }

private:

	//Health of the part
	UPROPERTY(EditDefaultsOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float maxPartHealth;

	//Health of the part
	UPROPERTY(EditDefaultsOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float partHealth;

	//amount of health the parts will regen
	UPROPERTY(EditDefaultsOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float healthRegenAmount;

	//The time it takes to regen health
	UPROPERTY(EditDefaultsOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float healthRegenTime;

	//Until next health regen
	float healthRegenTimeLeft;

	class APlayerRobot* mainBody;

protected:

	//Is the part to damaged to work
	bool damaged;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//Returns the players health
	UFUNCTION(BlueprintPure, Category = Health)
		float getPartHealth() { return partHealth; }

	//Damage part
	UFUNCTION(BlueprintCallable, Category = Health)
		void damage(float damage);

	UFUNCTION(BlueprintCallable, Category = Health)
		void addHealth(float healthAmount);

	//If the part has been fully damaged or heated they are no longer active
	UFUNCTION(BlueprintCallable, Category = Health)
		virtual bool isActive();

	UFUNCTION(BlueprintCallable, Category = Health)
	void Heal(float DeltaTime);

	
};