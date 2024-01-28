// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Pig.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APig::APig()
{
	WallDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("WallDetecetor"));
	WallDetector->SetupAttachment(RootComponent);
	WallDetector->SetRelativeLocation(FVector(35, 0, 0));
	WallDetector->SetBoxExtent(FVector(7, 32, 32));
	WallDetector->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WallDetector->SetCollisionResponseToAllChannels(ECR_Ignore);
	WallDetector->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

	LedgeDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("LedgeDetector"));
	LedgeDetector->SetupAttachment(RootComponent);
	LedgeDetector->SetRelativeLocation(FVector(45, 0, -30));
	LedgeDetector->SetBoxExtent(FVector(7, 32, 32));
	LedgeDetector->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LedgeDetector->SetCollisionResponseToAllChannels(ECR_Ignore);
	LedgeDetector->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void APig::BeginPlay()
{
	Super::BeginPlay();
	WallDetector->OnComponentBeginOverlap.AddDynamic(this, &APig::OnWallDetectorBeginOverlap);
}

void APig::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetCharacterMovement()->CurrentFloor.IsWalkableFloor()) 
	{
		LedgeDetector->GetOverlappingActors(LedgeOverlappingActors);
		if (LedgeOverlappingActors.IsEmpty())
		{
			if (OnDetectLedgeDelegate.IsBound())
			{
				OnDetectLedgeDelegate.Broadcast();
			}
		}
	}
}

void APig::Defeat()
{
	Super::Defeat();
}

void APig::OnWallDetectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OnDetectWallDelegate.IsBound())
	{
		OnDetectWallDelegate.Broadcast();
	}
}
