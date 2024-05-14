// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "LoadGameButton.generated.h"

/**
 * 
 */
UCLASS()
class THELOSTISLAND_API ULoadGameButton : public UButton
{
	GENERATED_BODY()

public:
	ULoadGameButton();

	UFUNCTION()
	void ClickedButton();
};
