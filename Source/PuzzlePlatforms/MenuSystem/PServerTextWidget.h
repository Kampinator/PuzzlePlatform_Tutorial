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
	
	
};
