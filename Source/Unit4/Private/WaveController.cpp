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

	defaultWave.num_waves = 5;
	defaultWave.wave_spawn_type_amt.SetNumZeroed(defaultWave.num_waves);
	

	defaultWave.wave_spawn_type_amt[0].enemy_spawn_amts.Emplace(5);
	defaultWave.wave_spawn_type_amt[0].enemy_spawn_amts.Emplace(5);

	defaultWave.wave_spawn_type_amt[1].enemy_spawn_amts.Emplace(10);
	defaultWave.wave_spawn_type_amt[1].enemy_spawn_amts.Emplace(5);

	defaultWave.wave_spawn_type_amt[2].enemy_spawn_amts.Emplace(12);
	defaultWave.wave_spawn_type_amt[2].enemy_spawn_amts.Emplace(12);

	defaultWave.wave_spawn_type_amt[3].enemy_spawn_amts.Emplace(10);
	defaultWave.wave_spawn_type_amt[3].enemy_spawn_amts.Emplace(10);

	defaultWave.wave_spawn_type_amt[4].enemy_spawn_amts.Emplace(15);
	defaultWave.wave_spawn_type_amt[4].enemy_spawn_amts.Emplace(15);

	for (int i = 0; i < defaultWave.wave_spawn_type_amt.Num(); i++) {
		for (int num : defaultWave.wave_spawn_type_amt[i].enemy_spawn_amts) {
			defaultWave.wave_spawn_type_amt[i].total_enemies += num;
		}
	}


	for (TActorIterator<AaiSpawner> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		aiSpawnerInLevel.Emplace(*ActorItr);
	}


	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AaiSpawner::StaticClass(), aiSpawnerInLevel);

	StartWave();
}

// Called every frame
void AWaveController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWaveStarted) {
		if (AiSpawned < AiToSpawnTotal) {
			if (TimeSinceLastSpawn <= TimeToSpawnEachAi) {
				TimeSinceLastSpawn += DeltaTime;
			}
			else {
				AiSpawned++;

				bool typeToSpawn = FMath::RandBool();

				if (typeToSpawn && ArchersSpawned < ArchersToSpawn) {
					ArchersSpawned++;
					aiSpawnerInLevel[0]->spawnAi(typeToSpawn);
					UE_LOG(LogTemp, Warning, TEXT("### SPAWNED ARCHER AI ###: %i"), ArchersSpawned);
				}
				else if (KnightsSpawned < KnightsToSpawn) {
					KnightsSpawned++;
					aiSpawnerInLevel[0]->spawnAi(typeToSpawn);
					UE_LOG(LogTemp, Warning, TEXT("### SPAWNED KNIGHT AI ###: %i"), KnightsSpawned);
				}
				TimeSinceLastSpawn = 0;
			}
		}
		else {
			AiInLevel.Empty();
			for (TActorIterator<AenemyAi> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
				AiInLevel.Emplace(*ActorItr);
			}

			if (AiInLevel.Num() == 0) {
				NextWaveCountDown -= DeltaTime;
				if (NextWaveCountDown < 0) { 
					bWaveStarted = false;
					StartWave(); 
				}
			}
		}
		
	}
}

void AWaveController::StartWave() {

	CurrentWave++;
	UE_LOG(LogTemp, Warning, TEXT("The current wave is: %i"), CurrentWave);

	AiDBLookup = defaultWave.wave_spawn_type_amt[CurrentWave - 1].total_enemies;
	UE_LOG(LogTemp, Warning, TEXT("Ai to spawn from DB is: %i"), AiDBLookup);

	AiToSpawnTotal = (AiDBLookup + (CurrentWave * Difficulty));
	UE_LOG(LogTemp, Warning, TEXT("Total Ai to spawn is: %i"), AiToSpawnTotal);

	KnightsToSpawn = defaultWave.wave_spawn_type_amt[CurrentWave - 1].enemy_spawn_amts[1];
	UE_LOG(LogTemp, Warning, TEXT("Knights to spawn: %i"), KnightsToSpawn);

	ArchersToSpawn = defaultWave.wave_spawn_type_amt[CurrentWave - 1].enemy_spawn_amts[1];
	UE_LOG(LogTemp, Warning, TEXT("Archers to spawn: %i"), ArchersToSpawn);

	TotalTime = ((GR * AiToSpawnTotal) / Difficulty);
	UE_LOG(LogTemp, Warning, TEXT("The time to spawn over is: %f"), TotalTime);

	TimeToSpawnEachAi = (TotalTime / AiToSpawnTotal);
	UE_LOG(LogTemp, Warning, TEXT("This would spawn an AI every: %f"), TimeToSpawnEachAi);

	bWaveStarted = true;
	NextWaveCountDown = 3.f;


}