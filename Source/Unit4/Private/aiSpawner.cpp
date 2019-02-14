// Fill out your copyright notice in the Description page of Project Settings.

#include "aiSpawner.h"
#include <functional>


// Sets default values
AaiSpawner::AaiSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AaiSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AaiSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AaiSpawner::spawnAi(bool type) {
	// Clear the array of spawnable areas
	spawnAreas.Empty(); 

	// find all spawnable areas
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), AspawnArea::StaticClass(), spawnAreas); // Find all areas

	int randomSpawnIndex = FMath::RandRange(0, spawnAreas.Num()-1);

	AspawnArea *temp = Cast<AspawnArea>(spawnAreas[randomSpawnIndex]);
	if (temp->spawnable) {
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *spawnAreas[randomSpawnIndex]->GetName()); // Check if they are spawnable
		// Spawn ai
		//temp->GetComponentsBoundingBox();
		TArray<UBoxComponent*> boxComps;
		temp->GetComponents(boxComps);

		UBoxComponent* Box = boxComps[0];
		FVector extent = Box->GetScaledBoxExtent(); // this is w,h,d

		//this wil generate random number between 0-w, 0-h,0-d. scaled. around the origin.
		//get the boxes location, and add it to the vector extents to project the point.
		FVector randomBoxPos = Box->GetComponentLocation() + FVector(FMath::RandRange(0.0f, extent.X),FMath::RandRange(0.0f, extent.Y),FMath::RandRange(0.0f, extent.Z));
		FRotator Rotation(0.0f, 0.0f, 0.0f);

		FTransform transform;
		transform.SetTranslation(randomBoxPos);
		transform.SetRotation(FQuat(Rotation));


		//UE_LOG(LogTemp, Log, TEXT("Trying to spawn class : %s"), *class_to_spawn->GetName());
		AenemyAi* SpawnedAi = Cast<AenemyAi>(GetWorld()->SpawnActor(class_to_spawn, &transform));

		if (SpawnedAi) {
			if (type) {
				SpawnedAi->UnitType_ = UnitType::Unit_archer;
				SpawnedAi->OnConstruction(SpawnedAi->GetTransform());
			}
		}

		//if (IsValid(SpawnedAi)) { UE_LOG(LogTemp, Log, TEXT("SpawnedAi is valid")); } else { UE_LOG(LogTemp, Log, TEXT("SPawnedAi is not valid")); }

		

	}

}