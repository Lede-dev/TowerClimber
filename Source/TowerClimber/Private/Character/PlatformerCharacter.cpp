// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlatformerCharacter.h"

#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/Ledge.h"

APlatformerCharacter::APlatformerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0, 1, 0));
}

void APlatformerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->GravityScale = MovementProperty.GravityScale;
	GetCharacterMovement()->JumpZVelocity = MovementProperty.JumpZVelocity;
	GetCharacterMovement()->AirControl = MovementProperty.AirControl;
}

void APlatformerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateOneWayPlatformCollision();
}

void APlatformerCharacter::Defeat()
{
	if (!bIsDefeated)
	{
		bIsDefeated = true;

		// Disable Collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Play Death Animation
		GetAnimationComponent()->GetAnimInstance()->JumpToNode(NameOfJumpToDefeatedNode);

		// Play Death Sound
		if (DeathSound)
		{
			UGameplayStatics::PlaySound2D(this, DeathSound);
		}
	}
}

void APlatformerCharacter::UpdateOneWayPlatformCollision()
{
	if (GetCharacterMovement()->IsFalling() && GetVelocity().Z < 0)
	{
		FHitResult Result;
		const FCollisionObjectQueryParams ObjectQueryParams = FCollisionObjectQueryParams(ECC_GameTraceChannel1);
		const FVector StartLocation = GetActorLocation();
		const FVector EndLocation = StartLocation + FVector::DownVector * PlatformCheckDistance;

#if WITH_EDITOR
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), true, 1, 1, 5.f);
#endif
		
		if (GetWorld()->LineTraceSingleByObjectType(Result, StartLocation, EndLocation, ObjectQueryParams))
		{
			if (const ALedge* Ledge = Cast<ALedge>(Result.GetActor()))
			{
				GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
			}
		}
		else
		{
			GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
		}
	}
}
