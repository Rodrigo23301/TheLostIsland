// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "USaveCustomButton.generated.h"

/**
 * 
 */
UCLASS()
class THELOSTISLAND_API UUSaveCustomButton : public UButton
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector PlayerLocation;

	UUSaveCustomButton();

	UFUNCTION()
	void ClickedButton();

};
