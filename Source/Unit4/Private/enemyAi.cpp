// Fill out your copyright notice in the Description page of Project Settings.

#include "enemyAi.h"




// Sets default values
AenemyAi::AenemyAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AenemyAi::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TargetActors);


}

// Called every frame
void AenemyAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (state_) {
	case State_idle:
		UE_LOG(LogTemp, Warning, TEXT("State_idle"));
		bCanPathfind = true;
		state_ = State_pathfind;
		break;

	case State_pathfind:
		if (bCanPathfind) {
			UE_LOG(LogTemp, Warning, TEXT("State_pathfind"));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetActors[0]->GetName());
			this->GetController()->MoveToActor();

			bCanPathfind = false;
		}
		break;

	case State_attack:
		UE_LOG(LogTemp, Warning, TEXT("State_pathfind"));
		break;
	}

}

// Called to bind functionality to input
void AenemyAi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}



