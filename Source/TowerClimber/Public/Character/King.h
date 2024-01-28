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

public:
	AKing();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Defeat() override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

};
