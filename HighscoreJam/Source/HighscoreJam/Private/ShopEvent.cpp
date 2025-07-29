// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopEvent.h"

// Sets default values
AShopEvent::AShopEvent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShopEvent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShopEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

