// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "InventoryController.h"
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

USTRUCT(BlueprintType)
struct FSSerializedObjectData
{
	GENERATED_BODY()
public:
	// Datos de texto
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Name"))
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Subname"))
	FString Subname;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Description"))
	FString Description;

	// Identificadores únicos para serialización
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ClassPath"))
	FString ClassPath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ObjectPath"))
	FString ObjectPath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ImagePath"))
	FString ImagePath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "StaticMeshPath"))
	FString StaticMeshPath;

	// Cantidad máxima
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxQuantity"))
	int32 MaxQuantity;
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

	UPROPERTY(VisibleAnywhere)
	TArray<FSSerializedObjectData> inventory;

	UPROPERTY(VisibleAnywhere)
	TArray<int32> quantitiesInventory;
};
