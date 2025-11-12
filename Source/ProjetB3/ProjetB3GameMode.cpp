// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetB3GameMode.h"
#include "ProjetB3Character.h"
#include "UObject/ConstructorHelpers.h"

AProjetB3GameMode::AProjetB3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
