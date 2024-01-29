// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Spring.h"

#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Character/PlatformerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASpring::ASpring()
{
	PrimaryActorTick.bCanEverTick = true;

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbook"));
	SetRootComponent(PaperFlipbookComponent);

	CharacterOverlapCheckBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CharacterOverlapCheckBox->SetupAttachment(PaperFlipbookComponent);
}

void ASpring::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (IdleFlipbook)
	{
		PaperFlipbookComponent->SetFlipbook(IdleFlipbook);
	}
}

void ASpring::BeginPlay()
{
	Super::BeginPlay();

	CharacterOverlapCheckBox->OnComponentBeginOverlap.AddDynamic(this, &ASpring::OnBeginOverlap);
	PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ASpring::OnFlipbookFinishedPlaying);
}

void ASpring::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlatformerCharacter* Character = Cast<APlatformerCharacter>(OtherActor))
	{
		if (Character->GetMovementComponent()->IsFalling() && Character->GetVelocity().Z < 0)
		{
			// Launch Character
			Character->LaunchCharacter(LaunchDirection * LaunchPower, false, true);

			// Play Animation
			if (LaunchFlipbook)
			{
				PaperFlipbookComponent->SetLooping(false);
				PaperFlipbookComponent->SetFlipbook(LaunchFlipbook);
				PaperFlipbookComponent->PlayFromStart();
			}
		}
	}
}

void ASpring::OnFlipbookFinishedPlaying()
{
	if (PaperFlipbookComponent && IdleFlipbook)
	{
		PaperFlipbookComponent->SetLooping(true);
		PaperFlipbookComponent->SetFlipbook(IdleFlipbook);
	}
}



