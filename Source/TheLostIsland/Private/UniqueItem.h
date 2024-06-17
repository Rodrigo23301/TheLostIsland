// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniqueItem.generated.h"

/**
 * 
 */
UCLASS()
class THELOSTISLAND_API UUniqueItem : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Item")
	int32 quantityItem;
	
};
