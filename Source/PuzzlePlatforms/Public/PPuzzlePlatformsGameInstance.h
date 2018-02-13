// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PPuzzlePlatformsGameInstance.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPPuzzlePlatformsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPPuzzlePlatformsGameInstance();
	virtual void Init() override;

	UFUNCTION(exec)
	void Host();

	UFUNCTION(exec)
	void Join(FString Address);

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

private:
	UPROPERTY()
	TSubclassOf<UUserWidget> MenuClass;
	
	
	
	
};
