// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobotPart.generated.h"

UCLASS()
class ROBOT_API ARobotPart : public AActor
{
	GENERATED_BODY()

	//Box collider
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	//	class UBoxComponent* UboxCollider;

	//Head we have connected
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* URobotMesh;
	
public:	
	// Sets default values for this actor's properties
	ARobotPart(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return URobotMesh; }

private:

	//Health of the part
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
		float partHealth;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//Damage part
	UFUNCTION(BlueprintCallable, Category = Health)
	void damage(float damage);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};