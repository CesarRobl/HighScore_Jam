// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurtleChar.generated.h"

UCLASS()
class HIGHSCOREJAM_API ATurtleChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurtleChar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turtle Properties")
	FVector SpawnLocation;

	float Health = 100.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	FVector GetNewTargetLocation(float Radius)
	{
		// Generate a random location within a certain radius around the spawn location
		float Angle = FMath::RandRange(0.0f, 2 * PI);
		float Distance = FMath::Sqrt(FMath::RandRange(0.0f, 1.0f)) * Radius;
		float X = Distance * FMath::Cos(Angle);
		float Y = Distance * FMath::Sin(Angle);
		return SpawnLocation + FVector(X, Y, 0.0f);
	}

};
