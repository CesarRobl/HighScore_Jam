// Fill out your copyright notice in the Description page of Project Settings.
#include "AIControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AAIControllerBase::AAIControllerBase()
{
	// Set this AI controller to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}