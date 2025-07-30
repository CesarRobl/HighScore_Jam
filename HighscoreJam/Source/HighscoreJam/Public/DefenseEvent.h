// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventBase.h"
#include "DefenseEvent.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSCOREJAM_API UDefenseEvent : public UEventBase
{
	GENERATED_BODY()
	\
public:
	virtual void StartEvent(UWorld* World) override
	{
		// Pick a random spawn point for the turtles
		int RandomIndex = FMath::RandRange(0, SpawnLocations.Num() - 1);
		FVector SpawnLocation = SpawnLocations[RandomIndex];

		TArray<FVector> TrianglePoints;
		float radius = 300.0f; // Radius for the triangle points
		FVector Center = SpawnLocation;

		for(int i = 0; i < 3; i++)
		{
			float angle = i * (2 * PI / 3); // Divide the circle into 3 parts
			FVector Vertex = Center + FVector(radius * FMath::Cos(angle), radius * FMath::Sin(angle), 0.0f);

			TrianglePoints.Add(Vertex);
		}

		if (!TurtleClass)
		{
			UE_LOG(LogTemp, Error, TEXT("TurtleClass is not set!"));
			return;
		}

		if (World)
		{
			for (const FVector& SpawnPoints : TrianglePoints)
			{
				ATurtleChar* TestTurtle = World->SpawnActor<ATurtleChar>(TurtleClass, SpawnPoints, FRotator::ZeroRotator);

				SpawnedTurtles.Add(TestTurtle);
			}
		}

		
	}

	virtual void TickEvent(float DeltaTime) override
	{
		EventTimer -= DeltaTime;

		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, FString::Printf(TEXT("Event Timer: %.2f"), EventTimer));

		if (EventTimer <= 0)
		{
			if (CheckTurtlesAlive())
			{
				// If any turtle is still alive, reset the timer and continue the event
				WinState = EEventWinState::Win;
			}
			else
			{
				WinState = EEventWinState::Lose;
			}
			EndEvent();
		}
	}

	virtual void EndEvent() override
	{
		
		SpawnedTurtles.Empty();
		bIsEventActive = false;
		UE_LOG(LogTemp, Warning, TEXT("Defense Event Ended"));
	}
};
