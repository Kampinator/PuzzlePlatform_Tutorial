// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PPlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APPlatformTrigger::APPlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RealRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RealRoot;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComp"));
	TriggerBox->SetupAttachment(RealRoot);
	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMesh"));
	TriggerMesh->SetupAttachment(RealRoot);


}

// Called when the game starts or when spawned
void APPlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void APPlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

