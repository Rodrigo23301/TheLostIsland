// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class THELOSTISLAND_API UGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	class UButton* saveButton;
	
	virtual void NativeConstruct() override;

	void BotonClickeado();
};
