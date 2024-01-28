// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlatformerCharacter.h"

#include "PaperZDAnimationComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlatformerCharacter::APlatformerCharacter()
{
	PaperAnimationComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("PaperAnimationComponent"));
	
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
}

void APlatformerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->GravityScale = MovementProperty.GravityScale;
	GetCharacterMovement()->JumpZVelocity = MovementProperty.JumpZVelocity;
	GetCharacterMovement()->AirControl = MovementProperty.AirControl;
}
