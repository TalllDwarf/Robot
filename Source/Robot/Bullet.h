// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Bullet.generated.h"

UCLASS()
class ROBOT_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Speed of the bullet
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float speed;

	//Lifetime of the bullet
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Life)
		float lifeTime = 3.4f;

	//Damage of the bullet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Life)
		float damage;

	//Returns the mesh to the blueprints
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return bulletMesh; }

	//Returns the box component for blueprints
	FORCEINLINE UBoxComponent* GetCollision() const { return boxCollision; }

private:

	//Bullet Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* bulletMesh;
	
	//collision
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* boxCollision;
};
