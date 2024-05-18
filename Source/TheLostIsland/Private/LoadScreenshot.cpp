// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadScreenshot.h"
#include "ImageUtils.h"

void ULoadScreenshot::ChargeScreenshot(FString slotName) {
    UTexture2D* screenshot = FImageUtils::ImportFileAsTexture2D(*(FPaths::ProjectDir() + TEXT("Saved/Screenshots/") + slotName + TEXT(".png")));

    FLinearColor TintColor = FLinearColor::White;
    FSlateBrush ImageBrush;
    ImageBrush.SetResourceObject(nullptr);
    if (screenshot)
    {
        TintColor = FLinearColor::White;
        ImageBrush.SetResourceObject(screenshot);
        ImageBrush.TintColor = FSlateColor(TintColor);
    }

    SetBrush(ImageBrush);
    SynchronizeProperties();
}


