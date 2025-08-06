// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopEvent.h"
#include "UpgradeManager.h"
#include "Kismet/GameplayStatics.h"


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
	UpgradeManager = Cast<AUpgradeManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AUpgradeManager::StaticClass()));
}

// Called every frame
void AShopEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AShopEvent::ShowWares()
{
	for (size_t i = 0; i < 3; i++)
	{
		AvailableUpgrades.Add(UpgradeManager->GetUpgrade());
	}
	
}