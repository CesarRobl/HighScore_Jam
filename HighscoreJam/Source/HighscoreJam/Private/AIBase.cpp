// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpawnManager.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame  .You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();
	SavedDelay = LaserDelay; // Initialize the saved delay time
	TargetCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	TargetLocation = TargetCharacter ? TargetCharacter->GetActorLocation() : FVector::ZeroVector;
}

// Called every frame
void AAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(AIStats.Health <= 0)
	{
		Die();
	}

}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIBase::TakeDamage() 
{
	LaserDelay -= GetWorld()->GetDeltaSeconds();

	if(LaserDelay <= 0.0f)
	{
		AIStats.Health -= AIStats.Damage; // Reduce health by damage amount
		LaserDelay = SavedDelay; // Reset the delay
		UE_LOG(LogTemp, Warning, TEXT("AI took damage! Health: %d"), AIStats.Health);
	}
}

void AAIBase::Die() 
{
	UE_LOG(LogTemp, Warning, TEXT("AI has died!"));

	USkeletalMeshComponent* MeshComp = GetMesh();

	ASpawnManager* SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnManager::StaticClass()));
	if (SpawnManager)
	{
		SpawnManager->SpawnedEnemies--;
	}
	if(MeshComp)
	{
		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
		
		
	}

	GetCharacterMovement()->DisableMovement();
}

void AAIBase::AttackTarget()
{
	if (TargetCharacter && DistanceToTarget() <= AttackRange && !bIsAttacking)
	{
		// Perform attack logic here, e.g., apply damage to the target character

		bIsAttacking = true;
		PlayAnimMontage(AttackMontage);
		GetCharacterMovement()->MaxWalkSpeed = AIStats.AttackWalkSpeed;

		GetWorldTimerManager().SetTimer(
			AttackTimerHandle,
			this,
			&AAIBase::ResetAttackState,
			AttackCooldown,
			false
		);
	}
}

void AAIBase::PerformAttack_Implementation()
{
	if (TargetCharacter)
	{
		// Logic to apply damage to the target character
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AI performed attack on target"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No target to attack"));
	}
}

