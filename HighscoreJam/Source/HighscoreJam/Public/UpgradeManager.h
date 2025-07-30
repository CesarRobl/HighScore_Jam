// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpgradeManager.generated.h"

USTRUCT(BlueprintType)
struct FPlayerUpgrade
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UpgradeCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Multiplier = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UpgradeName;
};

UCLASS()
class HIGHSCOREJAM_API AUpgradeManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpgradeManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades")
	TArray<FPlayerUpgrade> Upgrades;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable)
	FPlayerUpgrade GetUpgrade()
	{
		float TotalWeight = 0.0f;
		for(const FPlayerUpgrade& Upgrade : Upgrades)
		{
			TotalWeight += Upgrade.Weight;
		}

		float RandomValue = FMath::FRandRange(0.0f, TotalWeight);
		float CumulativeWeight = 0.0f;

		for(const FPlayerUpgrade& Upgrade : Upgrades)
		{
			CumulativeWeight += Upgrade.Weight;
			if(RandomValue <= CumulativeWeight)
			{
				return Upgrade;
			}
		}

		return FPlayerUpgrade();
	}

	UFUNCTION(BlueprintCallable)
	FString GetUpgradeDescription(const FPlayerUpgrade& Upgrade)
	{
		float Percentage = (Upgrade.Multiplier - 1.0f) * 100.0f;

		return FString::Printf(TEXT("Increase %s by %.2f%%"), *Upgrade.UpgradeName, Percentage);
	}
};
