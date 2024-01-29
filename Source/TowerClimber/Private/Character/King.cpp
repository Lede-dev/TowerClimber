// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/King.h"

#include "Camera/CameraComponent.h"
#include "Character/Pig.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

AKing::AKing()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

void AKing::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AKing::OnBeginOverlap);
}

bool AKing::CanJumpInternal_Implementation() const
{
	return Super::CanJumpInternal_Implementation() || bIsInCoyoteTime;
}

void AKing::OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal,
	const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta)
{
	bIsInCoyoteTime = true;
	
	FTimerManager& Timer = GetWorld()->GetTimerManager();
	if (Timer.IsTimerActive(CoyoteTimer))
	{
		Timer.ClearTimer(CoyoteTimer);
	}

	Timer.SetTimer(CoyoteTimer, [this]
	{
		bIsInCoyoteTime = false;
	}, CoyoteTimeLength, false);
}

void AKing::Defeat()
{
	Super::Defeat();
	
	// Disable Y Plane Constraint
	GetCharacterMovement()->SetPlaneConstraintEnabled(false);

	// Launch Player Character
	const FVector LaunchForward = GetActorForwardVector() * LaunchPowerWhenDefeated.X;
	const FVector LaunchUp = GetActorUpVector() * LaunchPowerWhenDefeated.Z;
	const FVector LaunchRight = GetActorRightVector() * LaunchPowerWhenDefeated.Y;
	LaunchCharacter(LaunchForward + LaunchUp + LaunchRight, true, true);

	// Detach Camera
	const FDetachmentTransformRules DetachRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);
	CameraBoom->DetachFromComponent(DetachRules);

	// Shake Camera
	UGameplayStatics::PlayWorldCameraShake(this, DefeatCameraShake, GetActorLocation(), 0.0f, 10000.0f, 0);
}

void AKing::SetJumpBuffering()
{
	bIsJumpBuffering = true;

	FTimerManager& Timer = GetWorld()->GetTimerManager();
	if (Timer.IsTimerActive(JumpBufferTimer))
	{
		Timer.ClearTimer(JumpBufferTimer);
	}

	Timer.SetTimer(JumpBufferTimer, [this]
	{
		bIsJumpBuffering = false;
	}, JumpBufferLength, false);
}

void AKing::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APig* Pig = Cast<APig>(OtherActor))
	{
		if (GetCharacterMovement()->IsFalling() && GetVelocity().Z < 0)
		{
			Pig->Defeat();

			// Launch Player Character
			const FVector LaunchForward = GetActorForwardVector() * LaunchPowerWhenKillEnemy.X;
			const FVector LaunchUp = GetActorUpVector() * LaunchPowerWhenKillEnemy.Z;
			const FVector LaunchRight = GetActorRightVector() * LaunchPowerWhenKillEnemy.Y;
			LaunchCharacter(LaunchForward + LaunchUp + LaunchRight, true, true);
		}
		else
		{
			Defeat();
		}
	}
}
