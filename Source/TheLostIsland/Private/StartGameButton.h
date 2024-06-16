// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "StartGameButton.generated.h"

/**
 * 
 */
UCLASS()
class UStartGameButton : public UButton
{
	GENERATED_BODY()

public:
	UStartGameButton();

	UFUNCTION()
	void ClickedButton();
	
};
