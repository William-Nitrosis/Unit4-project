// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AiCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class UNIT4_API AAiCharacterController : public AAIController
{
	GENERATED_BODY()
	
public:
	void findPathPls();
	
	
};

