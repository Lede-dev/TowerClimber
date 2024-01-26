// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlatformerCharacter.h"
#include "King.generated.h"

/**
 * 
 */
UCLASS()
class TOWERCLIMBER_API AKing : public APlatformerCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
