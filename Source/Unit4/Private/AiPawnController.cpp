// Fill out your copyright notice in the Description page of Project Settings.

#include "AiPawnController.h"



// Sets default values
AAiPawnController::AAiPawnController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAiPawnController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAiPawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void PathfindActor(AActor* enemyToMove)
{

}