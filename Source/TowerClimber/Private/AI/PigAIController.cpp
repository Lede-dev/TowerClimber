// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PigAIController.h"

#include "Character/Pig.h"

void APigAIController::BeginPlay()
{
	Super::BeginPlay();
}

void APigAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Enemy = MakeWeakObjectPtr(Cast<APig>(InPawn));

	if (Enemy.IsValid())
	{
		Enemy->OnDetectWallDelegate.AddUObject(this, &APigAIController::OnDetectWall);
		Enemy->OnDetectLedgeDelegate.AddUObject(this, &APigAIController::OnDetectLedge);
	}
}

void APigAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Enemy.IsValid())
	{
		Enemy->AddMovementInput(Enemy->GetActorForwardVector(), 1.0f);
	}
}

void APigAIController::RotateCharacter() const
{
	if (Enemy.IsValid())
	{
		Enemy->SetActorRotation(Enemy->GetActorRotation() + FRotator(0, 180, 0));
	}
}

void APigAIController::OnDetectWall()
{
	RotateCharacter();
}

void APigAIController::OnDetectLedge()
{
	RotateCharacter();
}
