// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/PMenuInterface.h"
#include "OnlineSessionInterface.h"
#include "PPuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPPuzzlePlatformsGameInstance : public UGameInstance, public IPMenuInterface
{
	GENERATED_BODY()

public:
	UPPuzzlePlatformsGameInstance();
	virtual void Init() override;

	// Interface functions
	void Host_Implementation();
	void Join_Implementation(int32 index);
	void RefreshServerList_Implementation();
	
	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	IOnlineSessionPtr SessionInterface;
	void SessionCreated(FName SessionName, bool CreatedSuccesfully);
	void SessionDestroyed(FName SessionName, bool CreatedSuccesfully);
	void SessionsFound(bool FoundSessions);
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);



private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MenuClass;

	class UPMainMenu* Menu;	
	
	
};
