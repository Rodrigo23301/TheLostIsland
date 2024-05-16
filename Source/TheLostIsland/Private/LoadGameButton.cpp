// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "LoadGameButton.h"

ULoadGameButton::ULoadGameButton()
{
	OnClicked.AddDynamic(this, &ULoadGameButton::ClickedButton);
}

void ULoadGameButton::ClickedButton()
{
	FString slotName;

	if (auto baseGameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		GetName(slotName);
		baseGameInstance->LoadGame(slotName);
	}
}