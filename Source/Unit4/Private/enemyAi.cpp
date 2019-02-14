// Fill out your copyright notice in the Description page of Project Settings.

#include "enemyAi.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AenemyAi::AenemyAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UE_LOG(LogTemp, Error, TEXT("UnitType_ as string : %s"), *GETENUMSTRING("UnitType", UnitType_));

	TimeLeftOnAttack = AttackCooldown;

	// Add objects and set params
	RangeSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RangeSphere"));
	//RangeSphereComponent->bHiddenInGame = true;
	RangeSphereComponent->SetupAttachment(RootComponent);
	RangeSphereComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	RangeSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AenemyAi::OnRangeSphereBeginOverlap);
	RangeSphereComponent->OnComponentEndOverlap.AddDynamic(this, &AenemyAi::OnRangeSphereEndOverlap);
}

void AenemyAi::OnConstruction(const FTransform & Transform)
{
	// Data lookup and variable setting
	switch (UnitType_)
	{
	case UnitType::Unit_knight:
		AttackRange = 150.f;
		AttackDamage = 25.f;
		AttackCooldown = 3.f;
		DamageType = UDamageType::StaticClass();
		this->GetMesh()->SetSkeletalMesh(SK_knight);
		this->GetMesh()->SetAnimInstanceClass(Anim_knight);
		//UE_LOG(LogTemp, Warning, TEXT("Set unit type KNIGHT"));
		MeshOffset = FRotator(0.f, 0.f, 0.f);
		this->GetMesh()->AddLocalRotation(MeshOffset);
		break;

	case UnitType::Unit_archer:
		AttackRange = 1000.f;
		AttackDamage = 10.f;
		AttackCooldown = 2.f;
		DamageType = UDamageType::StaticClass();
		this->GetMesh()->SetSkeletalMesh(SK_archer);
		this->GetMesh()->SetAnimInstanceClass(Anim_archer);
		//UE_LOG(LogTemp, Warning, TEXT("Set unit type ARCHER"));
		MeshOffset = FRotator(0.f, -90.f, 0.f);
		this->GetMesh()->AddLocalRotation(MeshOffset);
		break;
	}

	RangeSphereComponent->SetSphereRadius(AttackRange);
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
	bCanPathfind = false;

	if (state_ != State::State_attack)
	{
		state_ = State::State_idle;
	}
	
}


// Called every frame
void AenemyAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (state_) {
	case State::State_idle:
			//UE_LOG(LogTemp, Warning, TEXT("State_idle"));
			bCanPathfind = true;
			state_ = State::State_pathfind;
			break;

	case State::State_pathfind:
			if (bCanPathfind) {
				//UE_LOG(LogTemp, Warning, TEXT("State_pathfind"));
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetActors[0]->GetName());
				
				if (AiController) {
					AiController->MoveToActor(TargetActors[0], AttackRange, true, true, true, 0, true);
				}
				bCanPathfind = false;
			}
			break;

	case State::State_attack:
			this->GetCharacterMovement()->StopMovementImmediately();
			FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), attackTarget->GetActorLocation());
			PlayerRot.Pitch = 0.f;

			this->SetActorRotation(PlayerRot);

			TimeLeftOnAttack -= DeltaTime;
			if (IsValid(attackTarget))
			{
				if (TimeLeftOnAttack <= 0)
				{
					TimeLeftOnAttack = AttackCooldown;
				}
				break;
			} else
			{
				state_ = State::State_idle;
			}

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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
		//state_ = State_attack;
		//UE_LOG(LogTemp, Error, TEXT("%s"), *OtherActor->GetName());

		barricadePointer = Cast<Apo_barricade>(OtherActor);
		playerPointer = Cast<AplayerCharacter>(OtherActor);
		CrystalPointer = Cast<ACrystal>(OtherActor);


		if (barricadePointer || CrystalPointer)
		{
			attackTarget = OtherActor;
			state_ = State::State_attack;
		} else if (playerPointer && !bIgnorePlayer && state_ != State::State_attack)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap player"));
			attackTarget = OtherActor;
			bPlayerInRange = true;
			state_ = State::State_attack;
		}
	}
}

void AenemyAi::OnRangeSphereEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (OtherActor && (OtherActor != this) && OtherComp && !Cast<Apo_barricade>(attackTarget))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
		//state_ = State::State_idle;

		barricadePointer = Cast<Apo_barricade>(OtherActor);
		playerPointer = Cast<AplayerCharacter>(OtherActor);

		if (playerPointer && !bIgnorePlayer)
		{
			bPlayerInRange = false;
			state_ = State::State_idle;
		}
	}
}

void AenemyAi::tryDoDamage()
{
	if (IsValid(attackTarget))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DO DAMAGE"));
		UGameplayStatics::ApplyDamage(attackTarget, AttackDamage, this->AiController, this, DamageType);
	}
}

void AenemyAi::fireArrow()
{
	if (IsValid(attackTarget))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("FIRE ARROW"));
		//UGameplayStatics::ApplyDamage(attackTarget, AttackDamage, this->AiController, this, DamageType);

		FVector ArrowSpawnLocation = this->GetMesh()->GetSocketLocation("ArrowFirePoint");
		FRotator ArrowSpawnRotation =UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), attackTarget->GetActorLocation());
			
		FActorSpawnParameters ArrowSpawnInfo;
		ArrowSpawnInfo.Instigator = this;
		ArrowSpawnInfo.Owner = this;

		if (IsValid(ArrowDefault))
		{
			AActor* SpawnedArrow = GetWorld()->SpawnActor<AActor>(ArrowDefault, ArrowSpawnLocation, ArrowSpawnRotation, ArrowSpawnInfo);
		}

	}
}