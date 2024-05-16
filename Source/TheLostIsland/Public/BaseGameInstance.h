// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UBaseGameInstance();

	virtual void Init() override;

	void CreateSaveFile();

	void SaveGame();

	void LoadGame();
};
