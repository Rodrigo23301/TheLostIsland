// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "USaveCustomButton.h"

UUSaveCustomButton::UUSaveCustomButton()
{
	OnClicked.AddDynamic(this, &UUSaveCustomButton::ClickedButton);

	PlayerLocation = FVector(0.f, 0.f, 0.f);
}

void UUSaveCustomButton::ClickedButton()
{
	UE_LOG(LogTemp, Warning, TEXT("BotonClickeado se ha disparado"));

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	if (auto baseGameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
	{
		baseGameInstance->SaveGame();
	}
}