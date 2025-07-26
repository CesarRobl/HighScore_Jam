// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "AIBase.generated.h"

USTRUCT(BlueprintType)
struct FAIStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackWalkSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage = 5;
};

UCLASS()
class HIGHSCOREJAM_API AAIBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Stats")
	FAIStats AIStats;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	float DistanceToTarget() const 
	{
		if (!TargetCharacter) return 0.0f;

		return FVector::Dist(GetActorLocation(), TargetCharacter->GetActorLocation());
	}

	float LaserDelay = 0.5f; // Delay between getting hit and taking damage
	float SavedDelay = 0.0f; // Used to save the delay time

	FTimerHandle AttackTimerHandle; // Timer handle for attack cooldown

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Stats")
	float AttackRange = 200.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Stats")
	float AttackCooldown = 1.0f; 

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsAttacking = false; // Flag to check if the AI is currently attacking

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* TargetCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* AttackMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AI Actions")
	void AttackTarget();
	void ResetAttackState()
	{
		GetCharacterMovement()->MaxWalkSpeed = AIStats.Speed; // Reset walk speed after attack
		bIsAttacking = false;
	}

	UFUNCTION(BlueprintNativeEvent, Blueprintcallable, Category = "AI Actions")
	void PerformAttack();
	virtual void PerformAttack_Implementation();

	void TakeDamage();
	void Die();

	UFUNCTION(BlueprintCallable, Category = "AI Actions")
	bool IsDead() const 
	{
		return AIStats.Health <= 0;
	}
};
