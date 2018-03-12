// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerRobot.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/RobotPart.h"
#include "Player/RobotGun.h"
#include "Player/RobotLegPart.h"
#include "RobotGameMode.h"
#include "Engine.h"

// Sets default values
APlayerRobot::APlayerRobot()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	turnRate = 50.f;

	//Health
	healthRegenTime = healthRegenTimeLeft = 0.2f;
	healthRegenAmount = 2.5f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, turnRate, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

//returns if the player can strafe
bool APlayerRobot::canStrafe()
{
	if (legActor)
	{
		return legActor->canLegStrafe();
	}
	
	return true;
}

//Damages the player robot when health is 0 player dies
void APlayerRobot::damage(float damage)
{
	healthRemaining = FMath::Clamp((healthRemaining - damage), 0.0f, totalHealth);
	if (healthRemaining == 0.0f)
	{
		ARobotGameMode* gm = (ARobotGameMode*)GetWorld()->GetAuthGameMode();
		gm->changeState(-1);
	}
}

//Health the players robot
void APlayerRobot::heal(float healthAmount)
{
	healthRemaining = FMath::Clamp((healthRemaining + healthAmount), 0.0f, totalHealth);

	if (headActor)
	{
		headActor->addHealth(healthAmount);
	}

	for (auto& arm : leftArms)
	{
		arm->addHealth(healthAmount);
	}

	for (auto& arm : rightArms)
	{
		arm->addHealth(healthAmount);
	}

	if (legActor)
	{
		legActor->addHealth(healthAmount);
	}
}

//Adds time for the player to heal
void APlayerRobot::addHealTime(float healTime)
{
	healingTime += healTime;
}

// Called when the game starts or when spawned
void APlayerRobot::BeginPlay()
{
	Super::BeginPlay();	
}

void APlayerRobot::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		if (legActor->canLegsRotate())
		{
			const FRotator Rotation = legActor->GetActorRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, value);
		}
		else
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, value);

			if (legActor->isLegAGyro())
			{
				legActor->forwardAxis(value);
			}
		}
	}
	
	if (legActor)
	{
		//Are we currently moving
		legActor->IsMoving(value != 0);
	}
}

void APlayerRobot::MoveRight(float value)
{
	if (value != 0.0f)
	{
		if ((Controller != NULL) && canStrafe())
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, value);

			if (legActor->isLegAGyro())
			{
				legActor->rightAxis(value);
			}
		}
		else if (legActor)
		{
			if (legActor->canLegsRotate())
			{
				legActor->MoveRight(value);
			}
		}
	}
}

void APlayerRobot::TurnAtRate(float rate)
{
	float movement = rate * turnRate * GetWorld()->GetDeltaSeconds();
	// calculate delta for this frame from the rate information
	AddControllerYawInput(movement);

	//Dont rotate the legs if the legs are rotating alone
	if (legActor)
	{
		if(legActor->canLegsRotate())
			legActor->ReverseParentRotation();
	}
}

void APlayerRobot::LookUpAtRate(float rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(rate * turnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerRobot::GamepadForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && !legActor->canLegsRotate())
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, value);
	}
	else if (legActor)
	{
		if (legActor->canLegsRotate())
		{
			legActor->updateGamepadMovement(value, GetInputAxisValue(TEXT("GamepadRight")), FRotator(0, GetActorRotation().Yaw, 0));

			const FRotator Rotation = legActor->GetActorRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, FMath::Abs(value));
		}
	}
}

void APlayerRobot::GamepadRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && canStrafe())
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, value);
	}
	else if (legActor)
	{
		if (legActor->canLegsRotate())
		{
			legActor->updateGamepadMovement(GetInputAxisValue(TEXT("GamepadForward")), value, FRotator(0, GetActorRotation().Yaw, 0));

			const FRotator Rotation = legActor->GetActorRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, FMath::Abs(value));
		}
	}
}

// Called every frame
void APlayerRobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (healingTime > 0.0f)
	{
		healthRegenTimeLeft -= DeltaTime;

		if (healthRegenTimeLeft <= 0.0f)
		{
			healthRegenTimeLeft = healthRegenTime;

			heal(healthRegenAmount);

			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1.0f, FColor::Blue, "Healing");
		}
		healingTime -= DeltaTime;
	}
}

// Called to bind functionality to input
void APlayerRobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerRobot::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerRobot::MoveRight);
	PlayerInputComponent->BindAxis("GamepadForward", this, &APlayerRobot::GamepadForward);
	PlayerInputComponent->BindAxis("GamepadRight", this, &APlayerRobot::GamepadRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerRobot::TurnAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerRobot::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerRobot::LookUpAtRate);
}

