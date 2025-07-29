// Fill out your copyright notice in the Description page of Project Settings.


#include "EventsManager.h"
#include "DefenseEvent.h"

// Sets default values
AEventsManager::AEventsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventsManager::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentEvent = NewObject<UDefenseEvent>(this);
	if (CurrentEvent)
	{
		CurrentEvent->SpawnLocations = SpawnLocations; // Set spawn locations for the event
		CurrentEvent->TurtleClass = TurtleClass; // Set the turtle class for the event
		CurrentEvent->StartEvent(GetWorld()); // Start the event

		
	}
}

// Called every frame
void AEventsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

