// Copyright Epic Games, Inc. All Rights Reserved.

#include "HighscoreJamGameMode.h"
#include "HighscoreJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHighscoreJamGameMode::AHighscoreJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
