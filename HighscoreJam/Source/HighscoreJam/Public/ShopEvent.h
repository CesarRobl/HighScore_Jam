// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpgradeManager.h"
#include "ShopEvent.generated.h"

UCLASS()
class HIGHSCOREJAM_API AShopEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShopEvent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ShopDuration = 10.0f;
	
	AUpgradeManager* UpgradeManager;
	TArray<FPlayerUpgrade> AvailableUpgrades;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowWares();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowShopUI();
	void ShowShopUI_Implementation()
	{
		// Default C++ behavior (can be empty)
	}

};
