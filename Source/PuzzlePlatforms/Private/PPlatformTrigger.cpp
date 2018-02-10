// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PPlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

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

void APPlatformTrigger::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APPlatformTrigger, bIsOverlapped);
}



// Called when the game starts or when spawned
void APPlatformTrigger::BeginPlay()
{
	Super::BeginPlay();	
	if(HasAuthority())
	{
	//	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APPlatformTrigger::OnOverlapBegin);
	//	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APPlatformTrigger::OnOverlapEnd);
	}
	
}

// Called every frame
void APPlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APPlatformTrigger::GetIsOverlapped()
{
	return bIsOverlapped;
}

// Called every frame
/*
void APPlatformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
}

void APPlatformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End Overlapped"));
}*/

void APPlatformTrigger::NotifyActorBeginOverlap(AActor * OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlapped2"));
	if (HasAuthority())
	{
		bIsOverlapped = true;
	}
	
}

void APPlatformTrigger::NotifyActorEndOverlap(AActor * OtherActor)
{
	if (HasAuthority())
	{
		bIsOverlapped = false;
	}
}






