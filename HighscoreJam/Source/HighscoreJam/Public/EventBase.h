// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TurtleChar.h"
#include "EventBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEventWinState : uint8
{
	None UMETA(DisplayName = "None"),
	Win UMETA(DisplayName = "Win"),
	Lose UMETA(DisplayName = "Lose")
};

UCLASS()
class HIGHSCOREJAM_API UEventBase : public UObject
{
	GENERATED_BODY()

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		float EventTimer = 10;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float EventDuration = 1;

		bool bIsEventActive = true;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<ATurtleChar> TurtleClass;

		TArray<ATurtleChar*> SpawnedTurtles;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TArray<FVector> SpawnLocations;

		EEventWinState WinState = EEventWinState::None;

	public:
		virtual void StartEvent(UWorld* World);

		virtual void TickEvent(float DeltaTime);

		virtual void EndEvent();

		bool CheckTurtlesAlive()
		{
			for (ATurtleChar* Turtle : SpawnedTurtles)
			{
				if (Turtle->Health >= 0)
					return true; // If any turtle is alive, return true
			}

			return false; // otherwise, return false
		}
};
