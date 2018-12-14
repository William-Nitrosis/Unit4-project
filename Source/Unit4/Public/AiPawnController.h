// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "enemyAi.h"
#include "GameFramework/Actor.h"
#include "AiPawnController.generated.h"

UCLASS()
class UNIT4_API AAiPawnController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAiPawnController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PathfindActor(AActor* enemyToMove);

	TArray<AActor*> AiActorsTargets;
	TArray<AActor*> AiActors;
	
};
