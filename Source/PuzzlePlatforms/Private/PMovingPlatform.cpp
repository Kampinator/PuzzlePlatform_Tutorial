// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PMovingPlatform.h"
#include "Kismet/KismetMathLibrary.h"

APMovingPlatform::APMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
	// Speed which platform moves
	PlatformSpeed = 100;

	Forward = true;
	
}





void APMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		// We are going to replicate this actors movement.
		SetReplicates(true);
		SetReplicateMovement(true);
		GlobalStartLocation = GetActorLocation();
		// Change local position to Global position of this Vector.
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

	}
	
}

void APMovingPlatform::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	
	// Are we server
	if (HasAuthority())
	{	
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		// We compare if we are going forward or backward and are we at the Start or the End location. Then change the boolean
		Forward && FVector((GlobalStartLocation - GetActorLocation())).Size() > FVector((GlobalStartLocation - GlobalTargetLocation)).Size() ? Forward = false : !Forward && FVector((GlobalTargetLocation - GetActorLocation())).Size() > FVector((GlobalTargetLocation - GlobalStartLocation)).Size() ? Forward = true : 0;
		FVector Location = GetActorLocation();		
		// Direction vector is Vector B - Vector A		
		// Location is X centimeters per seconds in specific direction
		Forward ? SetActorLocation(GetActorLocation() + (PlatformSpeed * Deltatime * Direction)) : SetActorLocation(GetActorLocation() + (PlatformSpeed * Deltatime * Direction *-1));
	}

}
