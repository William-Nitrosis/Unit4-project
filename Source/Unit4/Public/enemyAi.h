// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Tasks/AITask.h"
#include "Tasks/AITask_MoveTo.h"
#include "Engine.h"
#include "enemyAi.generated.h"

/*
USTRUCT()
struct FPlayerStateStruct
{
	GENERATED_BODY()

	UPROPERTY()
	int32 SampleInt32;

	//Constructor
	FPlayerStateStruct()
	{
		SampleInt32 = 5;
	}
};

// Enum AiType
enum AiType
{
AiType_Orc,
AiType_Goblin,
AiType_Ogre
};
AiType AiType_ = AiType_Goblin;

*/


UCLASS()
class UNIT4_API AenemyAi : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AenemyAi();

	enum State
	{
		State_idle,
		State_pathfind,
		State_attack
	};
	State state_ = State_idle;

	bool bCanPathfind = true;
	TArray<AActor*> TargetActors;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ClassToFind; // Needs to be populated somehow (e.g. by exposing to blueprints as uproperty and setting it there
	AAIController * AiController;

	float AttackRange = 400.f;
	USphereComponent* RangeSphereComponent;

	UFUNCTION()
	void OnRangeSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnRangeSphereEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void OnMoveCompleted(FAIRequestID id, const FPathFollowingResult& result);


};