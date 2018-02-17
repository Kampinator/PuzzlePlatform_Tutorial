// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PPuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/PMainMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#define SESSION_NAME "MySession"

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
	// Get pointer to OnlineSubsystem
	IOnlineSubsystem* OnlineSubSystem = IOnlineSubsystem::Get();
	if (OnlineSubSystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem! %s!"), *OnlineSubSystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubSystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
				SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPPuzzlePlatformsGameInstance::SessionCreated);
				SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPPuzzlePlatformsGameInstance::SessionDestroyed);			
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Didn't found Subsystem! "));
	}

	


}


void UPPuzzlePlatformsGameInstance::LoadMenuWidget()
{
	if (MenuClass)
	{	
		Menu = CreateWidget<UPMainMenu>(this, MenuClass);
		Menu->Setup();
	}
	
}


void UPPuzzlePlatformsGameInstance::Host_Implementation() 
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;

		FNamedOnlineSession* SessionName = SessionInterface->GetNamedSession(SESSION_NAME);
		if (SessionName)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			SessionInterface->CreateSession(0, TEXT(SESSION_NAME), SessionSettings);
		}	
	}
}

void UPPuzzlePlatformsGameInstance::Join_Implementation(FString& IPAddress)
{
	UE_LOG(LogTemp, Warning, TEXT("Jeje"));
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{		
		PlayerController->ClientTravel(FString(IPAddress), ETravelType::TRAVEL_Absolute);
	}
	//UGameplayStatics::OpenLevel(this, FName("84.251.196.183")); 
}


void UPPuzzlePlatformsGameInstance::SessionCreated(FName SessionName, bool CreatedSuccesfully)
{
	if (CreatedSuccesfully)
	{
		UWorld* World = GetWorld();
		if (World)
		{
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Yellow, FString::Printf(TEXT("World is valid")));
		}
	}

	else
	UE_LOG(LogTemp, Warning, TEXT("Cannot create session"));

}

void UPPuzzlePlatformsGameInstance::SessionDestroyed(FName SessionName, bool CreatedSuccesfully)
{
	FOnlineSessionSettings SessionSettings;
	SessionInterface->CreateSession(0, TEXT(SESSION_NAME), SessionSettings);
}


