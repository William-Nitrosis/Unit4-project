// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"
#include "playerCharacter.generated.h"

UCLASS()
class UNIT4_API AplayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AplayerCharacter();

	// shooting variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShooting = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float scale = 0.7f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAiming = false;

	UPROPERTY(EditAnywhere)
	float mouseWheelScale = 10.f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input functions
	void moveForward(float AxisValue);
	void moveSide(float AxisValue);
	void MouseWheel(float inputValue);
	void MouseX(float inputValue);
	void MouseY(float inputValue);
	void jump();

	void shootDown();
	void shootUp();
	void aimingDown();
	void aimingUp();
	// Input variables
	FVector2D MovementInput;
	float mouseWheelValue;

	UCameraComponent* TP_Camera;
	UCameraComponent* FP_Camera;
	USpringArmComponent* SpringArm;

	void ActivateCam();
	void ToggleCameraPressed();
	void ToggleCameraReleased();
	bool firstPerson = true;
};
