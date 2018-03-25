// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PMenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORMS_API IPMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu System")
	void Host(); // This has empty implementation

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu System")
	void Join(FString& IPAddress); // This has empty implementation

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu System")
	void RefreshServerList(); // This has empty implementation


	
	
};
