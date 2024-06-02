// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameData.h"
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

	UBaseGameInstance();

	virtual void Init() override;

	void CreateSaveFile(FString slotName);

	void CreateSaveFile(FString slotName, FVector position, float health, TArray<FBuildings> buildings);

	void SaveGame(FString slotName);

	void LoadGame(FString slotName);

	TArray<FBuildings> SaveBuildings();

	void LoadBuildings(TArray<FBuildings> buildings);

	void SaveScreenshot(FString slotName);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealthBySlot(FString slotName);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHungerBySlot(FString slotName);

	UFUNCTION(BlueprintCallable)
	float GetCurrentThirstBySlot(FString slotName);

	bool CheckEnabledSlot(FString slotName);
};
