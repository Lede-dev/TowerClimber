// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PigAIController.generated.h"

class UBoxComponent;
class APig;
/**
 * 
 */
UCLASS()
class TOWERCLIMBER_API APigAIController : public AAIController
{
	GENERATED_BODY()

protected:
	TWeakObjectPtr<APig> Enemy;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

public:
	void RotateCharacter() const;

private:
	UFUNCTION()
	void OnDetectWall();

	UFUNCTION()
	void OnDetectLedge();
	
};
