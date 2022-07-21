// Copyright Epic Games, Inc. All Rights Reserved.


#include "SandboxGameModeBase.h"
#include "SandboxPlayerController.h"

ASandboxGameModeBase::ASandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}