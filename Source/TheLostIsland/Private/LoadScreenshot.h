// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "LoadScreenshot.generated.h"

/**
 * 
 */
UCLASS()
class ULoadScreenshot : public UImage
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChargeScreenshot(FString slotName);
};
