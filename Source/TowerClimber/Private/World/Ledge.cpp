// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Ledge.h"

#include "PaperSpriteComponent.h"

ALedge::ALedge()
{
	PrimaryActorTick.bCanEverTick = true;

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComponent"));
	SetRootComponent(PaperSpriteComponent);
	PaperSpriteComponent->TranslucencySortPriority = 1;
	PaperSpriteComponent->SetCollisionProfileName(TEXT("OneWayPlatform"));
}

