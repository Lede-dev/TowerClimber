// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PlatformerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/King.h"

APlatformerController::APlatformerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	KingCharacter = MakeWeakObjectPtr(Cast<AKing>(GetCharacter()));
}

void APlatformerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlatformerController::MoveCharacter);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &APlatformerController::JumpCharacter);
	}
}

void APlatformerController::MoveCharacter(const FInputActionValue& Value)
{
	const float Direction = Value.Get<float>();
	KingCharacter->AddMovementInput(FVector(Direction * MovementSpeed, 0, 0));

	if (Direction > 0)
	{
		SetControlRotation(FRotator::ZeroRotator);
	}
	else if (Direction < 0)
	{
		SetControlRotation(FRotator(0, 180, 0));
	}
}

void APlatformerController::JumpCharacter()
{
	KingCharacter->Jump();
}