// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PPuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/PMainMenu.h"

static int32 CheatSuperJump = 0;
FAutoConsoleVariableRef CVARCheatSuperJumpfaa(
	TEXT("CHEATS.SuperJump"),
	CheatSuperJump,
	TEXT("Allows user to jump higher"),
	ECVF_SetByConsole);





UPPuzzlePlatformsGameInstance::UPPuzzlePlatformsGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (WidgetClass.Class != nullptr)
	{
		MenuClass = WidgetClass.Class;
		UE_LOG(LogTemp, Warning, TEXT("Found Widget %s!"), *MenuClass->GetName());
	}
}

void UPPuzzlePlatformsGameInstance::Init()
{

}





void UPPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass)
	{	
		Menu = CreateWidget<UPMainMenu>(this, MenuClass);
		Menu->Setup();
	}
	
}

void UPPuzzlePlatformsGameInstance::Host_Implementation() 
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Yellow, FString::Printf(TEXT("World is valid")));
	}
}

void UPPuzzlePlatformsGameInstance::Join_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Jeje"));
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(FString("34324"), ETravelType::TRAVEL_Absolute);
	}
	//UGameplayStatics::OpenLevel(this, FName("84.251.196.183")); 
}



