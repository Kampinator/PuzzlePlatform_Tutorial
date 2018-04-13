// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PPuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/PMainMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

#include "VoiceInterface.h"
#include "VoiceDataCommon.h"

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
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPPuzzlePlatformsGameInstance::SessionsFound);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPPuzzlePlatformsGameInstance::OnJoinSessionComplete);
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
			FOnlineSessionSettings SessionSettings;
			SessionSettings.bIsLANMatch = true;
			SessionSettings.NumPublicConnections = 2;
			// Game shows in game list.
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bUsesPresence = true;
			// Create the session.
			SessionInterface->CreateSession(0, TEXT(SESSION_NAME), SessionSettings);
		}	
	}
}

void UPPuzzlePlatformsGameInstance::Join_Implementation(int32 index)
{
	if (SessionInterface.IsValid())
	{
		if (Menu)
		{
			UE_LOG(LogTemp, Warning, TEXT("Jeje"));
			Menu->SetServerList({ "Moikka", "Juuh" });

			SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[index]);

		}
	}
}

void UPPuzzlePlatformsGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (SessionInterface.IsValid())
	{
		FString ConnectInfo;
		if (SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo))
		{
			UE_LOG(LogTemp, Warning, TEXT("JoinCompleted"));
			APlayerController* PlayerController = GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(ConnectInfo, ETravelType::TRAVEL_Absolute);
			}
			//UGameplayStatics::OpenLevel(this, FName("84.251.196.183")); 
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not get ConnectString"));
		}


	}

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
	SessionSettings.bIsLANMatch = true;
	SessionSettings.NumPublicConnections = 2;
	// Game shows in game list.
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	// Create the session.
	SessionInterface->CreateSession(0, TEXT(SESSION_NAME), SessionSettings);
}

void UPPuzzlePlatformsGameInstance::SessionsFound(bool FoundSessions)
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to find sessions"));
	if (FoundSessions)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Finished found sessions"));
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		TArray<FString> ServerNames;
		for (auto Result : SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Something found"));
			ServerNames.Add(Result.GetSessionIdStr());
			FString SessionID = Result.Session.GetSessionIdStr();
			//UE_LOG(LogTemp, Warning, TEXT("Session : %s"), *SessionID);
		}
		Menu->SetServerList(ServerNames);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Sessions Found"));
	}

}

void UPPuzzlePlatformsGameInstance::RefreshServerList_Implementation()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->MaxSearchResults = 1000;
		//SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}



