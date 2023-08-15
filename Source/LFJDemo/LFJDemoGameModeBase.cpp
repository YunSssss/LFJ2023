// Copyright Epic Games, Inc. All Rights Reserved.


#include "LFJDemoGameModeBase.h"
#include "Characters/MainPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ALFJDemoGameModeBase::ALFJDemoGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawn(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_PlayerChar.BP_PlayerChar_C'"));
	if (PlayerPawn.Class!=NULL)
	{
		DefaultPawnClass = PlayerPawn.Class;
	}

	PlayerControllerClass = AMainPlayerController::StaticClass();
}
