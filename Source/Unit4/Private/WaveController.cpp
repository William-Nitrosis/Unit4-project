// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveController.h"


// Sets default values
AWaveController::AWaveController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



// say wave has started to the ai spawner.