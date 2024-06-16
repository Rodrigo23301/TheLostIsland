// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameButton.h"
#include "BaseGameInstance.h"

UStartGameButton::UStartGameButton()
{
	OnClicked.AddDynamic(this, &UStartGameButton::ClickedButton);
}

void UStartGameButton::ClickedButton()
{
	FString slotName;

	if (auto baseGameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		baseGameInstance->LoadLastGame();
	}
}