// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/PMenuInterface.h"
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

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwt;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinGameButtonn;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_BackToMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ServerListScrollBox;

	

public:
	UPMainMenu(const FObjectInitializer& ObjectInitializer);
	// Remember to call super with override!
	virtual bool Initialize() override;
	void Construct();
	void Setup();

	virtual void OnLevelRemovedFromWorld(class ULevel* InLevel, class UWorld* InWorld) override;
	

protected:
	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	UFUNCTION()
	void JoinGameButtonClicked();

	UFUNCTION()
	void BackToMenu();

private:
	TSubclassOf<class UUserWidget> ServerTextClass;



	
	
	
	
};
