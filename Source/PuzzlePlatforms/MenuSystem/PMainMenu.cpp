// Fill out your copyright notice in the Description page of Project Settings.

#include "PMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "MenuSystem/PMenuInterface.h"
#include "Kismet/GameplayStatics.h"


bool UPMainMenu::Initialize()
{
	Super::Initialize();
	HostBtn->OnClicked.AddDynamic(this, &UPMainMenu::HostButtonClicked);
	JoinBtn->OnClicked.AddDynamic(this, &UPMainMenu::JoinButtonClicked);
	JoinGameButtonn->OnClicked.AddDynamic(this, &UPMainMenu::JoinGameButtonClicked);
	Button_BackToMenu->OnClicked.AddDynamic(this, &UPMainMenu::BackToMenu);
	return true;
}

void UPMainMenu::Setup()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		this->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("Loaded Menu"));
		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(this->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = true;
	}
}

// Overrided Function from UWidget
void UPMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, class UWorld* InWorld)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		this->RemoveFromViewport();
		UE_LOG(LogTemp, Warning, TEXT("Loaded Menu"));
		FInputModeGameOnly InputModeData;
		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = false;
	}
}




// Interface calls
void UPMainMenu::HostButtonClicked()
{
	IPMenuInterface::Execute_Host(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UPMainMenu::JoinButtonClicked()
{
	//IPMenuInterface::Execute_Join(UGameplayStatics::GetGameInstance(GetWorld()));
	WidgetSwt->SetActiveWidget(JoinMenu);
}

void UPMainMenu::BackToMenu()
{
	//IPMenuInterface::Execute_Join(UGameplayStatics::GetGameInstance(GetWorld()));
	WidgetSwt->SetActiveWidget(HostMenu);
}

void UPMainMenu::JoinGameButtonClicked()
{
	FString IPText = *(IpAddressText->GetText().ToString());
	IPMenuInterface::Execute_Join(UGameplayStatics::GetGameInstance(GetWorld()), IPText);	
}



