// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheLostIslandGameMode.h"
#include "TheLostIslandCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheLostIslandGameMode::ATheLostIslandGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
