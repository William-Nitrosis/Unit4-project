// Fill out your copyright notice in the Description page of Project Settings.

#include "placeableObject.h"


// Sets default values
AplaceableObject::AplaceableObject()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AplaceableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AplaceableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AplaceableObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

