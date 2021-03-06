// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PMovingPlatform.generated.h"

class APPlatformTrigger;

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
	virtual void BeginPlay() override;
	virtual void Tick(float Deltatime) override;

private:
	UPROPERTY(EditAnywhere, Category ="Settings")
	float PlatformSpeed;

	UPROPERTY(EditAnywhere, Category = "Settings", Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

	bool Forward;
	bool bCanMove;

	UPROPERTY(EditInstanceOnly)
	bool MovedThroughTrigger;
	UPROPERTY(EditInstanceOnly, meta = (editcondition = MovedThroughTrigger))
	TArray<APPlatformTrigger*> ActivatingTriggers;



	
	
	
	
};
