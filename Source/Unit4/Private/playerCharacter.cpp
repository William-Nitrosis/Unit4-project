// Fill out your copyright notice in the Description page of Project Settings.

#include "playerCharacter.h"
#include "enemyAi.h"


// Sets default values
AplayerCharacter::AplayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AplayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<UCameraComponent*> cameraComps;
	GetComponents(cameraComps);

	/*for (int i = 0; i < cameraComps.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(cameraComps[i]->GetName()));
	}*/

	FP_Camera = cameraComps[0];
	TP_Camera = cameraComps[1];

	TArray<USpringArmComponent*> springComps;
	GetComponents(springComps);

	/*for (int i = 0; i < springComps.Num(); i++) {
		`
	}*/

	SpringArm = springComps[0];

	ActivateCam();
	
}

// Called every frame
void AplayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AplayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//axis bind the function events
	PlayerInputComponent->BindAxis("moveForward", this, &AplayerCharacter::moveForward);
	PlayerInputComponent->BindAxis("moveSide", this, &AplayerCharacter::moveSide);

	PlayerInputComponent->BindAxis("MouseX", this, &AplayerCharacter::MouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &AplayerCharacter::MouseY);

	PlayerInputComponent->BindAction("jump", IE_Pressed, this, &AplayerCharacter::jump);

	PlayerInputComponent->BindAction("shoot", IE_Pressed, this, &AplayerCharacter::shootDown);
	PlayerInputComponent->BindAction("shoot", IE_Released, this, &AplayerCharacter::shootUp);

	PlayerInputComponent->BindAction("aiming", IE_Pressed, this, &AplayerCharacter::aimingDown);
	PlayerInputComponent->BindAction("aiming", IE_Released, this, &AplayerCharacter::aimingUp);

	PlayerInputComponent->BindAxis("MouseWheel", this, &AplayerCharacter::MouseWheel);

	PlayerInputComponent->BindAction("toggleCamera", IE_Pressed, this, &AplayerCharacter::ToggleCameraPressed);
	PlayerInputComponent->BindAction("toggleCamera", IE_Released, this, &AplayerCharacter::ToggleCameraReleased);
}

//Input functions
void AplayerCharacter::moveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	this->AddMovementInput(this->GetActorForwardVector(), MovementInput.X, false);
}

void AplayerCharacter::moveSide(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	this->AddMovementInput(this->GetActorRightVector(), MovementInput.Y, false);
}

void AplayerCharacter::jump()
{
	this->Jump();
}

void AplayerCharacter::MouseX(float AxisValue)
{
	this->AddControllerYawInput(AxisValue * scale);
}

void AplayerCharacter::MouseY(float AxisValue)
{
	this->AddControllerPitchInput(AxisValue * scale);
}

void AplayerCharacter::shootDown()
{ /*
	UE_LOG(LogTemp, Warning, TEXT("SHOOTING"));
	//Hit contains information about what the raycast hit.
	TArray<FHitResult> Hits;
	FHitResult HitData(ForceInit);

	//The length of the ray in units.
	//For more flexibility you can expose a public variable in the editor
	float RayLength = 400;

	//The Origin of the raycast
	FVector StartLocation = SpringArm->GetForwardVector();

	//The EndLocation of the raycast
	FVector EndLocation = StartLocation + (StartLocation * RayLength);

	//Collision parameters. The following syntax means that we don't want the trace to be complex
	FCollisionQueryParams CollisionParameters;

	bool rayCast = GetWorld()->LineTraceMultiByChannel(Hits, StartLocation, EndLocation, ECC_Visibility, CollisionParameters);

	if (rayCast) {

		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			FColor(255, 0, 0),
			false, -1, 0,
			12.333
		);


		for (FHitResult& HitData : Hits)
		{
			if (HitData.GetActor()) // pointer check
			{
				AenemyAi* enemy = Cast<AenemyAi>(HitData.GetActor()); // Type Check
				if (!enemy) return; // Pointer Check

				UGameplayStatics::ApplyDamage(enemy, 10.f, this->GetController(), this, DamageType);
			}
		}
	}*/
}

void AplayerCharacter::shootUp()
{
	

}

void AplayerCharacter::aimingDown()
{
	bAiming = true;
	GetCharacterMovement()->MaxWalkSpeed = 350;
}

void AplayerCharacter::aimingUp()
{
	bAiming = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AplayerCharacter::MouseWheel(float inputValue) {
	mouseWheelValue = inputValue;

	FVector springDistance = TP_Camera->GetComponentLocation() - SpringArm->GetComponentLocation();
	float springLength = springDistance.Size();

	if (springLength - (mouseWheelValue * mouseWheelScale) < 160 || springLength - (mouseWheelValue * mouseWheelScale) > 350) {

	}
	else {
		SpringArm->TargetArmLength -= (mouseWheelValue * mouseWheelScale);
	}

}

void AplayerCharacter::ActivateCam() {
	TP_Camera->SetActive(!firstPerson);
	FP_Camera->SetActive(firstPerson);
}

void AplayerCharacter::ToggleCameraPressed() {
	//toggle and switch camera.
	firstPerson = !firstPerson;
	ActivateCam();
}

void AplayerCharacter::ToggleCameraReleased() {

}