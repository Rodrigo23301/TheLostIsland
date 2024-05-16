// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameData.h"
#include "GameFramework/Character.h"

UBaseGameInstance::UBaseGameInstance() 
{
	maxHealth = 100.f;
	currentHealth = 100.f;
}

void UBaseGameInstance::Init()
{
	Super::Init();

	//Load the game
	LoadGame();
}

void UBaseGameInstance::CreateSaveFile()
{
	//Create a SaveGame object and save to the default slot
	USaveGameData* dataToSave = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	UGameplayStatics::SaveGameToSlot(dataToSave, "Slot1", 0);
}

void UBaseGameInstance::SaveGame()
{
	//Initializa data to save
	USaveGameData* dataToSave = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));
	FVector position = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	//If there is a valid SaveGame object to use for saving
	if (dataToSave != nullptr)
	{
		dataToSave->characterPosition = position;
		dataToSave->health = currentHealth;
		UGameplayStatics::SaveGameToSlot(dataToSave, "Slot1", 0);
	}
	else if (!UGameplayStatics::DoesSaveGameExist("Slot1", 0))
	{
		//Create a default save file
		CreateSaveFile();
	}
}

void UBaseGameInstance::LoadGame()
{
	//Retrieve data to load
	USaveGameData* dataToLoad = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot("Slot1", 0));

	//Cast to MyCharacter
	ACharacter* MyCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Variables to set the Character Location
	bool bSweep = false;
	FHitResult OutSweepHitResult;
	ETeleportType Teleport = ETeleportType::None;

	//If there is valid dato to load
	if (dataToLoad != nullptr)
	{
		if (MyCharacter)
		{
			MyCharacter->SetActorLocation(dataToLoad->characterPosition, bSweep, &OutSweepHitResult, Teleport);
		}
		currentHealth = dataToLoad->health;
	}
	else if (!UGameplayStatics::DoesSaveGameExist("Slot1", 0))
	{
		//Create a default save file
		CreateSaveFile();
	}
}