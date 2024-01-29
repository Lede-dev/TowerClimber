// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "PlatformerController.generated.h"

class AKing;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class TOWERCLIMBER_API APlatformerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* RestartAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	float MovementSpeed;
	
private:
	TWeakObjectPtr<AKing> KingCharacter;

public:
	APlatformerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void MoveCharacter(const FInputActionValue& Value);
	void JumpCharacter();
	void RestartGame();
	
};


