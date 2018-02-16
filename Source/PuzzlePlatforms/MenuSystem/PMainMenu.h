// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPMainMenu : public UUserWidget
{
	GENERATED_BODY()

	
	UPROPERTY(meta = (BindWidget))
	class UButton* HostBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinBtn;

public:
	// Remember to call super with override!
	virtual bool Initialize() override;
	void Construct();

protected:
	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();
	
	
	
};
