// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "spawnArea.h"
#include "enemyAi.h"
#include "aiSpawner.generated.h"

UCLASS(BlueprintType)
class UNIT4_API AaiSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AaiSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void spawnAi();

	TArray<AActor*> spawnAreas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AenemyAi> class_to_spawn;
	
};
