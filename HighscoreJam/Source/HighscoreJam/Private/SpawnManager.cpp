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
	SavedRoundInterval = RoundInterval; // Save the initial round interval
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(EnemyCount >= MaxEnemyCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("All enemies have been spawned!"));
		WaitNextRound(); // Call the function to wait for the next round
		
		return; // Exit if there are no enemies left to spawn
	}

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
		FRotator::ZeroRotator 
		);

	EnemyCount--;

	if (EnemyCount <= 0)
	{
		CurrentRound++;
		RoundInterval = SavedRoundInterval; // Reset the round interval after spawning all enemies
	}
}

void ASpawnManager::WaitNextRound() {
	
	RoundInterval -= GetWorld()->GetDeltaSeconds(); // Decrease the round interval by the delta time

	if (RoundInterval <= 0) {
		EnemyCount = 0;
		MaxEnemyCount += 5; // Increase the maximum enemy count for the next round add Dynamic difficulty scaling here if needed
	}

	if(CurrentRound >= MaxRounds) {
		UE_LOG(LogTemp, Warning, TEXT("Maximum rounds reached!"));
		return; // Exit if the maximum number of rounds has been reached
	}
	
	

	// Optionally, you can add logic to increase difficulty or change enemy types here
	UE_LOG(LogTemp, Warning, TEXT("Waiting for next round: %d"), CurrentRound);
}

