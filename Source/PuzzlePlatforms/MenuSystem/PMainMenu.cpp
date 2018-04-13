// Fill out your copyright notice in the Description page of Project Settings.

#include "PMainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "MenuSystem/PMenuInterface.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/PServerTextWidget.h"




// Menu = CreateWidget<UPMainMenu>(this, MenuClass);


UPMainMenu::UPMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/MenuSystem/WBP_ServerText"));
	if (WidgetClass.Class != nullptr)
	{
		ServerTextClass = WidgetClass.Class;
		//UE_LOG(LogTemp, Warning, TEXT("Found Widget %s!"), *MenuClass->GetName());
	}
}

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
	IPMenuInterface::Execute_RefreshServerList(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UPMainMenu::BackToMenu()
{
	//IPMenuInterface::Execute_Join(UGameplayStatics::GetGameInstance(GetWorld()));
	WidgetSwt->SetActiveWidget(HostMenu);
}

void UPMainMenu::SetServerList(TArray<FString> ServerNames)
{
	ServerListScrollBox->ClearChildren();
	uint32 i = 0;
	for (const FString& ServerName : ServerNames)
	{
		UE_LOG(LogTemp, Warning, TEXT("FOUND SOMETHING"));
		UPServerTextWidget* Row = CreateWidget<UPServerTextWidget>(this->GetWorld(), ServerTextClass);
		if (!ensure(Row != nullptr)) return;
		Row->ServerName->SetText(FText::FromString(ServerName));
		Row->Setup(this, i);
		++i;
		ServerListScrollBox->AddChild(Row);
	}
}

void UPMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
}

void UPMainMenu::JoinGameButtonClicked()
{
	if (SelectedIndex.IsSet())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Index: %d"), SelectedIndex.GetValue());
		IPMenuInterface::Execute_Join(UGameplayStatics::GetGameInstance(GetWorld()), SelectedIndex.GetValue());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Selected Index not set"));
	}

	

}



