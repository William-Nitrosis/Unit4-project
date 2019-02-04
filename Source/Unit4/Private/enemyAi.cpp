// Fill out your copyright notice in the Description page of Project Settings.

#include "enemyAi.h"

// Sets default values
AenemyAi::AenemyAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// add the shit to the object
	RangeSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RangeSphere"));
	RangeSphereComponent->bHiddenInGame = false;
	RangeSphereComponent->SetSphereRadius(AttackRange);
	RangeSphereComponent->SetupAttachment(RootComponent);
	RangeSphereComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	RangeSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AenemyAi::OnRangeSphereBeginOverlap);
	RangeSphereComponent->OnComponentEndOverlap.AddDynamic(this, &AenemyAi::OnRangeSphereEndOverlap);
}

// Called when the game starts or when spawned
void AenemyAi::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TargetActors);
	AiController = Cast<AAIController>(this->GetController());
	AiController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AenemyAi::OnMoveCompleted);
	
}

void AenemyAi::OnMoveCompleted(FAIRequestID id, const FPathFollowingResult& result) {
	UE_LOG(LogTemp, Warning, TEXT("path done bruh!"));
}


// Called every frame
void AenemyAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (state_) {
		case State_idle:
			UE_LOG(LogTemp, Warning, TEXT("State_idle"));
			bCanPathfind = true;
			state_ = State_pathfind;
			break;

		case State_pathfind:
			if (bCanPathfind) {
				UE_LOG(LogTemp, Warning, TEXT("State_pathfind"));
				UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetActors[0]->GetName());

				if (AiController) {
					AiController->MoveToActor(TargetActors[0], AttackRange, true, true, true, 0, true);

				}
				bCanPathfind = false;
			}
			break;

		case State_attack:
			UE_LOG(LogTemp, Warning, TEXT("State_pathfind"));
			break;
	}

}

// Called to bind functionality to input
void AenemyAi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}


void AenemyAi::OnRangeSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void AenemyAi::OnRangeSphereEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
	}
}