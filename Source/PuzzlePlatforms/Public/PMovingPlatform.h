// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PMovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API APMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	APMovingPlatform();

protected:
	virtual void Tick(float Deltatime) override;

private:
	UPROPERTY(EditAnywhere, Category ="Settings")
	float PlatformSpeed;
	
	
	
	
};
