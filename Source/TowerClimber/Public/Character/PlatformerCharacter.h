// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "PlatformerCharacter.generated.h"


USTRUCT(BlueprintType)
struct FMovementProperty
{
	GENERATED_BODY()

public:
	FMovementProperty():
	GravityScale(3.0f),
	JumpZVelocity(1100.0f),
	AirControl(0.3f)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpZVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AirControl;
};

UCLASS()
class TOWERCLIMBER_API APlatformerCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UPaperZDAnimationComponent* PaperAnimationComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platformer")
	FMovementProperty MovementProperty;
	
public:
	APlatformerCharacter();

protected:
	virtual void BeginPlay() override;
	
};
