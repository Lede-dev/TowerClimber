// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spring.generated.h"

class UBoxComponent;
class UPaperFlipbookComponent;
class UPaperFlipbook;

UCLASS()
class TOWERCLIMBER_API ASpring : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* PaperFlipbookComponent;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CharacterOverlapCheckBox;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring")
	UPaperFlipbook* IdleFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring")
	UPaperFlipbook* LaunchFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring")
	FVector LaunchDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spring")
	float LaunchPower;
	
public:	
	ASpring();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFlipbookFinishedPlaying();
	
};
