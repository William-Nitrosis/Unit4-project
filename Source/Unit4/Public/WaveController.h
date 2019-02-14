// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "WaveController.generated.h"

UCLASS()
class UNIT4_API AWaveController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	float GR = 1.61803399;

	float Difficulty = 1;
	int CurrentWave = 0;
	int AiDBLookup = 0;
	int AiToSpawnTotal = 0;

};
