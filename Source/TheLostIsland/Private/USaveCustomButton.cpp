// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "USaveCustomButton.h"

UUSaveCustomButton::UUSaveCustomButton()
{
	OnClicked.AddDynamic(this, &UUSaveCustomButton::ClickedButton);

	PlayerLocation = FVector(0.f, 0.f, 0.f);
	SetIsEnabled(false);
}

void UUSaveCustomButton::ClickedButton()
{
	FString slotName;

	if (auto baseGameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		GetName(slotName);
		baseGameInstance->SaveGame(slotName);
	}
}