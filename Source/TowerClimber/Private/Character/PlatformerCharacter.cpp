// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlatformerCharacter.h"

#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

APlatformerCharacter::APlatformerCharacter()
{
	PaperAnimationComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("PaperAnimationComponent"));
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
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

void APlatformerCharacter::Defeat()
{
	if (!bIsDefeated)
	{
		bIsDefeated = true;

		// Disable Collision
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Play Death Animation
		PaperAnimationComponent->GetAnimInstance()->JumpToNode(NameOfJumpToDefeatedNode);

		// Play Death Sound
		if (DeathSound)
		{
			UGameplayStatics::PlaySound2D(this, DeathSound);
		}
	}
}
