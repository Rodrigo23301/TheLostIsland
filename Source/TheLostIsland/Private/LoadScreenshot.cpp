// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadScreenshot.h"
#include "ImageUtils.h"

void ULoadScreenshot::ChargeScreenshot(FString slotName) {
    UTexture2D* screenshot = FImageUtils::ImportFileAsTexture2D(*(FPaths::ProjectDir() + TEXT("Saved/Screenshots/") + slotName + TEXT(".png")));

    FLinearColor TintColor = FLinearColor::White; // Cambia esto a tu color preferido
    FSlateBrush ImageBrush;

    if (screenshot)
    {
        TintColor = FLinearColor::White; // Cambia esto a tu color preferido
        ImageBrush.SetResourceObject(screenshot);
        ImageBrush.TintColor = FSlateColor(TintColor);
    }

    SetBrush(ImageBrush);
    SynchronizeProperties();
}


