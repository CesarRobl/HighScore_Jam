// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventBase.h"
#include "TurtleChar.h"
#include "DefenseEvent.h"
#include "EventsManager.generated.h"

UCLASS()
class HIGHSCOREJAM_API AEventsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnLocations; // Array of spawn locations for events

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATurtleChar> TurtleClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UEventBase* CurrentEvent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsEventActive = true;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SwitchEventUI();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowRewardsUI();

	void ShowRewardsUI_Implementation() 
	{
		// Default C++ behavior (can be empty)
	}


	UFUNCTION(BlueprintCallable, Category = "Events")
	void SpawnEvent() {
		CurrentEvent = NewObject<UDefenseEvent>(this);
		if (CurrentEvent)
		{
			bIsEventActive = true; // Set the event as active
			CurrentEvent->SpawnLocations = SpawnLocations; // Set spawn locations for the event
			CurrentEvent->TurtleClass = TurtleClass; // Set the turtle class for the event
			CurrentEvent->StartEvent(GetWorld()); // Start the event
			SwitchEventUI();
		}
	}

	
};
