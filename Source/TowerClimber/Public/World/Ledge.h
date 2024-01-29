// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ledge.generated.h"

class UPaperSprite;
class UPaperSpriteComponent;


UCLASS()
class TOWERCLIMBER_API ALedge : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* PaperSpriteComponent;

protected:
	UPROPERTY()
	bool bIsOneWay;

public:	
	ALedge();

};
