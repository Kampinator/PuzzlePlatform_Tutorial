// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPlatformTrigger.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class PUZZLEPLATFORMS_API APPlatformTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPlatformTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* RealRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TriggerMesh;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	
};
