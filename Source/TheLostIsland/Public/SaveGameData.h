// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"


USTRUCT()
struct FBuildings
{
	GENERATED_BODY()

	UPROPERTY()
	FString nameClass;

	UPROPERTY()
	FVector position;

	UPROPERTY()
	FRotator rotation;
};

USTRUCT()
struct FInteractable
{
	GENERATED_BODY()

	UPROPERTY()
	FString nameClass;

	UPROPERTY()
	FVector position;
};

USTRUCT()
struct FChopable
{
	GENERATED_BODY()

	UPROPERTY()
	FString nameClass;

	UPROPERTY()
	FVector position;
};

/**
 * 
 */
UCLASS()
class THELOSTISLAND_API USaveGameData : public USaveGame
{
	GENERATED_BODY()
	
public:
	USaveGameData();

	UPROPERTY(VisibleAnywhere)
	float health;

	UPROPERTY(VisibleAnywhere)
	float hunger;

	UPROPERTY(VisibleAnywhere)
	float thirst;

	UPROPERTY(VisibleAnywhere)
	FVector characterPosition;

	UPROPERTY(VisibleAnywhere)
	TArray<FBuildings> everyBuildMaster;

	UPROPERTY(VisibleAnywhere)
	TArray<FInteractable> everyInteractable;

	UPROPERTY(VisibleAnywhere)
	TArray<FChopable> everyChopable;
};
