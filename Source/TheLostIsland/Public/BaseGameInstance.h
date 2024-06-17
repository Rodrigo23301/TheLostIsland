// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameData.h"
#include "InventoryController.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THELOSTISLAND_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FVector characterPosition;

	FString slotToCharge;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	float maxHealth;

	UPROPERTY(BlueprintReadWrite, Category = "Health")
	float currentHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Hunger")
	float maxHunger;

	UPROPERTY(BlueprintReadWrite, Category = "Hunger")
	float currentHunger;

	UPROPERTY(BlueprintReadOnly, Category = "Thirst")
	float maxThirst;

	UPROPERTY(BlueprintReadWrite, Category = "Thirst")
	float currentThirst;

	UPROPERTY(BlueprintReadWrite, Category = "Load")
	bool isLoaded;

	UBaseGameInstance();

	virtual void Init() override;

	void CreateSaveFile(FString slotName);

	void CreateSaveFile(FString slotName, FVector position, float health, TArray<FBuildings> buildings);

	void SaveGame(FString slotName);

	void LoadGame(FString slotName);

	void LoadedGame();

	TArray<FBuildings> SaveBuildings();
	void LoadBuildings(TArray<FBuildings> buildings);

	TArray<FInteractable> SaveInteractables();
	void LoadInteractables(TArray<FInteractable> chopableActors);

	TArray<FChopable> SaveChopables();
	void LoadChopables(TArray<FChopable> chopableActors);

	TArray<FSSerializedObjectData> SaveInventory();
	TArray<int32> SaveQuantities();
	void LoadInventory(TArray<FSSerializedObjectData>& serializedInventory);
	void LoadQuantities(TArray<int32> quantities);
	bool DeserializeFSObjectData(const FSSerializedObjectData& SerializedData, FS_objectData& ObjectData);
	bool SerializeFSObjectData(const FS_objectData& ObjectData, FSSerializedObjectData& SerializedData);

	void SaveScreenshot(FString slotName);

	FString GetSaveGamePath(const FString& NombreArchivo);
	void LoadLastGame();

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealthBySlot(FString slotName);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHungerBySlot(FString slotName);

	UFUNCTION(BlueprintCallable)
	float GetCurrentThirstBySlot(FString slotName);

	bool CheckEnabledSlot(FString slotName);

	void HandleLevelLoaded(UWorld* World, const UWorld::InitializationValues IVS);
};
