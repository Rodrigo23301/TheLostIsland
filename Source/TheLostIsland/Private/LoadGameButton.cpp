// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadGameButton.h"
#include "BaseGameInstance.h"

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

bool ULoadGameButton::CheckEnabled()
{
	FString slotName;
	bool enabled = false;

	if (auto baseGameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		GetName(slotName);
		enabled = baseGameInstance->CheckEnabledSlot(slotName);
	}

	return enabled;
}
