// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PServerTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPServerTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget = true))
	class UTextBlock* ServerName;

	void Setup(class UPMainMenu* Parent, uint32 Index);

	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget = true))
	class UButton* RowButton;
	UPROPERTY()
	class UPMainMenu* Parent;
	uint32 Index;


	UFUNCTION()
	void RowButtonClicked();

	
};
