// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "HighscoreJamCharacter.generated.h"



USTRUCT(BlueprintType)
struct FPlayerStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Water = 50.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float WaterCapacity = 100.0f; 

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float WaterDrainRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaterRefillRate = 8.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CapsuleRadius = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CapsuleHalfHeight = 10.0f;
};

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AHighscoreJamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AHighscoreJamCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	FPlayerStats PlayerStats;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable)
	void Shoot();

	//** Called when the player is choked (e.g., out of water) */
	void Choke();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float HealthCapacity = 10.0f;

	float WaterCapacity = 100.0f; // Maximum water capacity
	float ChokeDelay = 0.0f; // Delay before choking starts
	bool bIsRefilling = false; // Flag to check if refilling is in progress
	

	
protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	virtual void RefillWater() 
	{
		bIsRefilling = true;
		PlayerStats.Water += GetWorld()->GetDeltaSeconds() * PlayerStats.WaterRefillRate;
		if (PlayerStats.Water >= PlayerStats.WaterCapacity) {
			PlayerStats.Water = PlayerStats.WaterCapacity; // Ensure water does not exceed capacity
		}
		
	}

	UFUNCTION(BlueprintCallable)
	void ApplyStatUpgrade(FString StatName, float Multiplier)
	{
		if (StatName == "Health")
		{
			PlayerStats.Health *= Multiplier;
			HealthCapacity *= Multiplier;
		}
			
		else if (StatName == "Damage")
			PlayerStats.Damage *= Multiplier;
		else if (StatName == "Water")
		{
			PlayerStats.Water *= Multiplier;
			PlayerStats.WaterCapacity *= Multiplier;
		}
		else if (StatName == "DrainRate")
			PlayerStats.WaterDrainRate *= Multiplier;
		else if (StatName == "RefillRate")
			PlayerStats.WaterRefillRate *= Multiplier;
		else if (StatName == "CapsuleRadius")
			PlayerStats.CapsuleRadius *= Multiplier;
		else if (StatName == "CapsuleHalfHeight")
			PlayerStats.CapsuleHalfHeight *= Multiplier;

	}

	UFUNCTION(BlueprintCallable)
	void SetRefillState(bool bRefilling)
	{
		bIsRefilling = bRefilling;
	}

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int32 DamageAmount)
	{
		PlayerStats.Health -= DamageAmount;
	}

	void Die()
	{
		USkeletalMeshComponent* MeshComp = GetMesh();

		if (MeshComp)
		{
			MeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			MeshComp->SetSimulatePhysics(true);	
			MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
		}
	}

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	bool IsDead() const
	{
		return PlayerStats.Health <= 0;
	}

	UFUNCTION(BlueprintCallable)
	void GetPercentage(float& HealthPercentage, float& WaterPercentage) const
	{
		HealthPercentage = PlayerStats.Health / HealthCapacity;
		WaterPercentage = PlayerStats.Water / PlayerStats.WaterCapacity;
	}
};



