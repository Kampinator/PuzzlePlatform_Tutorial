// Fill out your copyright notice in the Description page of Project Settings.

#include "PMainMenu.h"
#include "Components/Button.h"

bool UPMainMenu::Initialize()
{
	Super::Initialize();
	HostBtn->OnClicked.AddDynamic(this, &UPMainMenu::HostButtonClicked);
	JoinBtn->OnClicked.AddDynamic(this, &UPMainMenu::JoinButtonClicked);
	return true;
}

void UPMainMenu::HostButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("I am hosting a game"));
}

void UPMainMenu::JoinButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("I am Joining a gae"));
}