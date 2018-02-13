// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Rocket.generated.h"

UCLASS()
class ROBOT_API ARocket : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Speed of the Rocket
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float speed;

	//Lifetime of the Rocket
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Life)
		float lifeTime = 3.4f;

	//Damage of the Rocket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Life)
		float damage;

	//Returns the mesh to the blueprints
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return rocketMesh; }

	//Returns the box component for blueprints
	FORCEINLINE UBoxComponent* GetCollision() const { return boxCollision; }

private:

	//Rocket Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* rocketMesh;

	//collision
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxCollision;
};
