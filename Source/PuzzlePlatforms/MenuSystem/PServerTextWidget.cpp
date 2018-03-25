// Fill out your copyright notice in the Description page of Project Settings.

#include "PServerTextWidget.h"
#include "PMainMenu.h"
#include "Components/Button.h"


void UPServerTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
	RowButton->OnClicked.AddDynamic(this, &UPServerTextWidget::RowButtonClicked);
}

void UPServerTextWidget::Setup(class UPMainMenu* Parent, uint32 Index)
{
	if (Parent)
	{
		this->Parent = Parent;
		this->Index = Index;
	}
}



void UPServerTextWidget::RowButtonClicked()
{
	Parent->SelectedIndex = Index;

}

