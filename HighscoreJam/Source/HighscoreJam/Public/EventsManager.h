// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventBase.h"
#include "TurtleChar.h"
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

	UEventBase* CurrentEvent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
