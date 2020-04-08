// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LocationChangeWRotGameMode.h"
#include "LocationChangeWRotHUD.h"
#include "LocationChangeWRotCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALocationChangeWRotGameMode::ALocationChangeWRotGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALocationChangeWRotHUD::StaticClass();
}
