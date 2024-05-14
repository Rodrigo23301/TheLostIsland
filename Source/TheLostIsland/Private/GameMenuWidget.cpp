// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuWidget.h"
#include "Components/Button.h"

void UGameMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    saveButton = (UButton*)GetWidgetFromName(TEXT("SaveGameButton"));
    UE_LOG(LogTemp, Warning, TEXT("Test"));
    if (saveButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("Test2"));
        saveButton->OnClicked.AddDynamic(this, &UGameMenuWidget::BotonClickeado);
        UE_LOG(LogTemp, Warning, TEXT("Test3"));
    }
      
}

void UGameMenuWidget::BotonClickeado()
{

    UE_LOG(LogTemp, Warning, TEXT("BotonClickeado se ha disparado"));

    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
    // Aquí va tu lógica al hacer clic
}