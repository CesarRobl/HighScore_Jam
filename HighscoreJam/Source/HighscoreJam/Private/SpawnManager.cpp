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
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		AAIBase::StaticClass(),
		SpawnLocation,
		FRotator::ZeroRotator // Spawn with no rotation for now
		);

}

