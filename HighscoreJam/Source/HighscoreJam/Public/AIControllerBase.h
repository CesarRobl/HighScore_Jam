// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSCOREJAM_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
	protected:

		AAIControllerBase();
		virtual void BeginPlay() override;

		 
};
