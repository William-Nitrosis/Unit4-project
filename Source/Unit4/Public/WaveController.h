// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "aiSpawner.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "WaveController.generated.h"


USTRUCT()
struct FWaveData {
	GENERATED_BODY()

	UPROPERTY()
	int total_enemies;

	UPROPERTY()
	TArray<int> enemy_spawn_amts;
};

USTRUCT()
struct FRoundData {

	GENERATED_BODY()
		
	int num_waves;

	UPROPERTY()
	TArray<FWaveData>  wave_spawn_type_amt;//[[5,5],[10,5],[12,12],[10,10]]
};



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
	
	
	UPROPERTY()
	TArray<AaiSpawner*> aiSpawnerInLevel;

	UPROPERTY()
	TArray<AenemyAi*> AiInLevel;
	

	FRoundData defaultWave;



	float GR = 1.61803399;
	float Difficulty = 1.5f;

	

	int CurrentWave = 0;
	int AiDBLookup = 0;
	int AiToSpawnTotal = 0;
	int AiSpawned = 0;
	float TotalTime = 0;
	float CurrentTime = 0;
	float TimeSinceLastSpawn = 0;
	float TimeToSpawnEachAi = 0;

	int ArchersSpawned = 0;
	int ArchersToSpawn = 0;
	int KnightsSpawned = 0;
	int KnightsToSpawn = 0;


	float NextWaveCountDown = 3.f;
	bool bWaveStarted = false;
	


	void StartWave();
};

