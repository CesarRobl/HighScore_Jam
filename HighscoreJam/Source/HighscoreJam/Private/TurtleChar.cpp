// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleChar.h"

// Sets default values
ATurtleChar::ATurtleChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurtleChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurtleChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurtleChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

