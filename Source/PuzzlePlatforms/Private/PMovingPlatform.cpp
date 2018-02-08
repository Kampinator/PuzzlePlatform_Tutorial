// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PMovingPlatform.h"

APMovingPlatform::APMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	// Speed which platform moves
	PlatformSpeed = 100;
}





void APMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		// We are going to replicate this actors movement.
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	
}

void APMovingPlatform::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	// Are we server
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		// Location is X centimeters per seconds
		Location += FVector(PlatformSpeed * Deltatime, 0, 0);
		SetActorLocation(Location);
	}

}
