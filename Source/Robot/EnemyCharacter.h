// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RobotGameMode.h"
#include "GameFramework/Character.h"
#include "RobotGameMode.h"
#include "SoundDefinitions.h" 
#include "EnemyCharacter.generated.h"



UCLASS()
class ROBOT_API AEnemyCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's properties
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly)
	class USphereComponent* CollisionComp;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* EnemyMesh;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	

	/** called when something enters the sphere component */



	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree *BotBehavior;
		

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
		void takeDamage(int damage);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int health;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void die();

	UFUNCTION(BlueprintNativeEvent)
		void ragdoll();


	ARobotGameMode* gm;

	USoundCue* enemyHitCue;
	UAudioComponent * enemyHitAudio;

		




	


	
};
 
