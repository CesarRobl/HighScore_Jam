// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIBase.h"
#include "SpawnManager.generated.h"

UCLASS()
class HIGHSCOREJAM_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Settings")
	float MaxSpawnDistance = 1000.0f; // Maximum distance from the player to spawn enemies

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Settings")
	float MinSpawnDistance = 500.0f; // Minimum distance from the player to spawn enemies

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Settings")
	TArray<TSubclassOf<AAIBase>>EnemyList; // List of enemy classes to spawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Settings")
	float SpawnInterval = 5.0f; // Time interval between spawns

	float SavedSpawnInterval; // Variable to save the spawn interval


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PickSpawnPoint();

};
