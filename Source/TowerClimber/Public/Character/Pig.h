// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlatformerCharacter.h"
#include "Pig.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDetectWallDelegate)
DECLARE_MULTICAST_DELEGATE(FOnDetectLedgeDelegate)

class UBoxComponent;

UCLASS()
class TOWERCLIMBER_API APig : public APlatformerCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* WallDetector;

	UPROPERTY(EditAnywhere)
	UBoxComponent* LedgeDetector;

public:
	FOnDetectWallDelegate OnDetectWallDelegate;
	FOnDetectLedgeDelegate OnDetectLedgeDelegate;

private:
	UPROPERTY()
	TArray<AActor*> LedgeOverlappingActors;
	
public:
	APig();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void Defeat() override;

private:
	UFUNCTION()
	void OnWallDetectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
