// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PPuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"

static int32 CheatSuperJump = 0;
FAutoConsoleVariableRef CVARCheatSuperJumpfaa(
	TEXT("CHEATS.SuperJump"),
	CheatSuperJump,
	TEXT("Allows user to jump higher"),
	ECVF_SetByConsole);





UPPuzzlePlatformsGameInstance::UPPuzzlePlatformsGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("I am constructo"));
}

void UPPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("I am Int"));
}

void UPPuzzlePlatformsGameInstance::Host(FString Address)
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Yellow, FString("hello"));
}

void UPPuzzlePlatformsGameInstance::Join(FString Address)
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Yellow, FString::Printf(TEXT("Joining %s"), *Address));
}




