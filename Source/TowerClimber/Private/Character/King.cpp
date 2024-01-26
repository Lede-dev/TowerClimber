// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/King.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AKing::AKing()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

void AKing::BeginPlay()
{
	Super::BeginPlay();

	
}
