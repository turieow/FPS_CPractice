// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSProjectGameMode.h"
#include "FPSProjectHUD.h"
#include "FPSProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

void AFPSProjectGameMode::StartPlay()
{
	Super::StartPlay();

	UE_LOG(LogTemp, Log, TEXT("START"));
	check(GEngine != nullptr);

	UE_LOG(LogTemp, Log, TEXT("START"));
	// Display a debug message for five seconds
	// The -1 "Key" value argument prevents the message from begin updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
}
