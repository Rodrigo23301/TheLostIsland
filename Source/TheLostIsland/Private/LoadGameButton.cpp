// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadGameButton.h"

ULoadGameButton::ULoadGameButton()
{
	OnClicked.AddDynamic(this, &ULoadGameButton::ClickedButton);
}

void ULoadGameButton::ClickedButton()
{
	UE_LOG(LogTemp, Warning, TEXT("BotonClickeado se ha disparado"));

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
}