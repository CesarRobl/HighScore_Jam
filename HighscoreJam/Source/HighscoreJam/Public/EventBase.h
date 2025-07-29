// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TurtleChar.h"
#include "EventBase.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSCOREJAM_API UEventBase : public UObject
{
	GENERATED_BODY()

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		float EventTimer;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float EventDuration = 1;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<ATurtleChar> TurtleClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TArray<FVector> SpawnLocations;

	public:
		virtual void StartEvent(UWorld* World);

		virtual void TickEvent(float DeltaTime);

		virtual void EndEvent();

	
};
