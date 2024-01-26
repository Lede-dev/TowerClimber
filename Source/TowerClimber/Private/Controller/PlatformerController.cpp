// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/PlatformerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APlatformerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
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
	UE_LOG(LogTemp, Warning, TEXT("Move. Direction %f"), Direction);
}

void APlatformerController::JumpCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("Jump."));
}