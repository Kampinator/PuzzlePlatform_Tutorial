// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PPuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

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

void UPPuzzlePlatformsGameInstance::Host()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Yellow, FString::Printf(TEXT("World is valid")));
	}
}

void UPPuzzlePlatformsGameInstance::Join(FString Address)
{

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(FString("192.168.1.100"), ETravelType::TRAVEL_Absolute);
	}
	//UGameplayStatics::OpenLevel(this, FName("84.251.196.183"));
	 
}

void UPPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass)
	{
		
		UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
		Menu->AddToViewport();
		APlayerController* PlayerController = GetFirstLocalPlayerController();
		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("Loaded Menu"));
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(Menu->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = true;
		}

	}
	
}




