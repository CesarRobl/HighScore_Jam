// Fill out your copyright notice in the Description page of Project Settings.


#include "EventsManager.h"
#include "DefenseEvent.h"
#include "Kismet/GameplayStatics.h"

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
	
	
}

// Called every frame
void AEventsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentEvent)
	{
		switch (CurrentEvent->WinState)
		{
			case EEventWinState::Win:
				ShowRewardsUI(); // Show rewards UI
				UGameplayStatics::SetGamePaused(GetWorld(), true); // Pause the game
				CurrentEvent = nullptr; // Clear the current event
				break;

			case EEventWinState::Lose:
				//Handle lost logic here
				break;

			default:
				CurrentEvent->TickEvent(DeltaTime);
				break;
		}
	}
}

void AEventsManager::SwitchEventUI_Implementation()
{
    // Default C++ behavior (can be empty)
}





