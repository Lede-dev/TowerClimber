// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlatformerCharacter.h"
#include "King.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TOWERCLIMBER_API AKing : public APlatformerCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="King")
	FVector LaunchPowerWhenKillEnemy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="King")
	FVector LaunchPowerWhenDefeated;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="King")
	TSubclassOf<UCameraShakeBase> DefeatCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="King")
	float CoyoteTimeLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="King")
	float JumpBufferLength;
	
	UPROPERTY(VisibleAnywhere, Category="King")
	bool bIsInCoyoteTime;

	UPROPERTY(VisibleAnywhere, Category="King")
	bool bIsJumpBuffering;

private:
	FTimerHandle CoyoteTimer;
	FTimerHandle JumpBufferTimer;
	
public:
	AKing();

protected:
	virtual void BeginPlay() override;
	
	virtual bool CanJumpInternal_Implementation() const override;
	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;

public:
	virtual void Defeat() override;

	void SetJumpBuffering();
	bool IsJumpBuffering() const { return bIsJumpBuffering; }

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

};
