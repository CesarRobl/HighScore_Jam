// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NotifyAttack.generated.h"

/**
 * 
 */
UCLASS()
class HIGHSCOREJAM_API UNotifyAttack : public UAnimNotify
{
	GENERATED_BODY()

	public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;	

		
	
};
