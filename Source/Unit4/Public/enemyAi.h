// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Tasks/AITask.h"
#include "Tasks/AITask_MoveTo.h"
#include "Engine.h"
#include "po_barricade.h"
#include "playerCharacter.h"
#include "enemyAi.generated.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

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
UENUM(BlueprintType)
enum class State : uint8
{
	State_idle 	UMETA(DisplayName = "State_idle"),
	State_pathfind 	UMETA(DisplayName = "State_pathfind"),
	State_attack	UMETA(DisplayName = "State_attack")
};

UENUM(BlueprintType)
enum class UnitType : uint8
{
	Unit_knight 	UMETA(DisplayName = "Unit_knight"),
	Unit_archer 	UMETA(DisplayName = "Unit_archer")
};

UCLASS()
class UNIT4_API AenemyAi : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AenemyAi();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	State state_ = State::State_idle;

	bool bCanPathfind = true;
	TArray<AActor*> TargetActors;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ClassToFind; // Needs to be populated somehow (e.g. by exposing to blueprints as uproperty and setting it there
	AAIController * AiController;

	USphereComponent* RangeSphereComponent;

	UFUNCTION()
	void OnRangeSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnRangeSphereEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	virtual void OnConstruction(const FTransform& Transform) override;

	AActor* attackTarget;

	UFUNCTION(BlueprintCallable)
	void tryDoDamage();

	Apo_barricade* barricadePointer;
	AplayerCharacter* playerPointer;





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void OnMoveCompleted(FAIRequestID id, const FPathFollowingResult& result);


	FRotator MeshOffset = FRotator(0.f, 0.f, 0.f);
	// Load in meshes 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy SK and AN")
	USkeletalMesh* SK_knight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy SK and AN")
	UClass* Anim_knight;
	


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy SK and AN")
	USkeletalMesh* SK_archer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy SK and AN")
	UClass* Anim_archer;
	


	// === Character stats === //

	// Unit type to look up data for
	UnitType UnitType_ = UnitType::Unit_archer;


	// === Default values for lookup === //
	// Attack range of the weapon - ie sight length for ranged weapons
	UPROPERTY(EditAnywhere, Category = WeaponStat)
	float AttackRange = 0.f;

	// The damage of the weapon
	UPROPERTY(EditAnywhere, Category = WeaponStat)
	float AttackDamage = 0.f;

	// The time in seconds for each attack loop 
	UPROPERTY(EditAnywhere, Category = WeaponStat)
	float AttackCooldown = 0.f;

	// The type of damage
	UPROPERTY(EditAnywhere, Category = WeaponStat)
	TSubclassOf<UDamageType> DamageType;


	// Timing variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeLeftOnAttack = AttackCooldown;

	// Whether or not to ignore the player 
	bool bIgnorePlayer = FMath::RandRange(0, 1);;


	bool bPlayerInRange = false;


};