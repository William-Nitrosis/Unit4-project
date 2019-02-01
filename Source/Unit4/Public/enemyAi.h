// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "enemyAi.generated.h"


//If you want this to appear in BP, make sure to use this instead
//USTRUCT(BlueprintType)
USTRUCT()
struct FPlayerStateStruct
{
	GENERATED_BODY()

		//Always make USTRUCT variables into UPROPERTY()
		//    any non-UPROPERTY() struct vars are not replicated

		// So to simplify your life for later debugging, always use UPROPERTY()
		UPROPERTY()
		int32 SampleInt32;

	//If you want the property to appear in BP, make sure to use this instead
	//UPROPERTY(BlueprintReadOnly)
	UPROPERTY()
		AActor* TargetActor;

	//Constructor
	FPlayerStateStruct()
	{
		//Always initialize your USTRUCT variables!
		//   exception is if you know the variable type has its own default constructor
		SampleInt32 = 5;
		TargetActor = NULL;
	}
};

USTRUCT()
struct FPlayerStateStructInherited : public FPlayerStateStruct
{
	GENERATED_BODY()


	//Constructor
	FPlayerStateStructInherited()
	{
		//Always initialize your USTRUCT variables!
		//   exception is if you know the variable type has its own default constructor
		SampleInt32 = 5;
		TargetActor = NULL;
	}
};


UCLASS()
class UNIT4_API AenemyAi : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AenemyAi();

	//this is the highlander!
	static FPlayerStateStruct player_struct;
	static FPlayerStateStructInherited struct2;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};

