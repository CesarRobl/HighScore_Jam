// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "AIBase.h"
#include "GameFramework/Character.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	PickSpawnPoint(); // Call the function to pick a spawn point when the game starts
	SavedSpawnInterval = SpawnInterval; // Save the initial spawn interval
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(SpawnInterval <= 0.0f)
	{
		PickSpawnPoint(); // Call the function to pick a spawn point when the spawn interval is reached
		SpawnInterval = SavedSpawnInterval; // Reset the spawn interval
	}
	else
	{
		SpawnInterval -= DeltaTime; // Decrease the spawn interval by the delta time
	}

}

void ASpawnManager::PickSpawnPoint() {
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	float RandomAngle = FMath::RandRange(0.0f, 360.0f);
	float RandomDistance = FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);

	FVector SpawnLocation = PlayerLocation + FVector(
		FMath::Cos(FMath::DegreesToRadians(RandomAngle)) * RandomDistance,
		FMath::Sin(FMath::DegreesToRadians(RandomAngle)) * RandomDistance,
		0.0f // Leave for now, can be adjusted later
	);

	GetWorld()->SpawnActor<AAIBase>(
		EnemyList[0],
		SpawnLocation,
		FRotator::ZeroRotator // Spawn with no rotation for now
		);

}

