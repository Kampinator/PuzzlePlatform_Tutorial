// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PPuzzlePlatformsGameInstance.generated.h"

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
	void Host(FString Address);

	UFUNCTION(exec)
	void Join(FString Address);
	
	
	
	
};
