// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBaseGameMode.h"
#include "ProjectBaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectBaseGameMode::AProjectBaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
