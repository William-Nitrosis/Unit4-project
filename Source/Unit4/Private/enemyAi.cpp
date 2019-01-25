// Fill out your copyright notice in the Description page of Project Settings.

#include "enemyAi.h"
#include "Engine.h"



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
	


}

// Called every frame
void AenemyAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AenemyAi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}



