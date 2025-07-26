// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyAttack.h"
#include "AIBase.h"

void UNotifyAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp)
	{
		AActor* Owner = MeshComp->GetOwner();
		if (Owner) 
		{
			AAIBase* AIBase = Cast<AAIBase>(Owner);
			if (AIBase) 
			{
				AIBase->PerformAttack();
			}
		}
	}
}