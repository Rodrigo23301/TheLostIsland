// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameData.h"
#include "GameFramework/Character.h"
#include "BuildMasterBase.h"
#include "Engine/Engine.h"

UBaseGameInstance::UBaseGameInstance() 
{
	maxHealth = 100.f;
	currentHealth = 100.f;
}

void UBaseGameInstance::Init()
{
	Super::Init();

	//Load the game
	//LoadGame("Slot1");
}

void UBaseGameInstance::CreateSaveFile(FString slotName)
{
	//Create a SaveGame object and save to the default slot
	USaveGameData* dataToSave = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	UGameplayStatics::SaveGameToSlot(dataToSave, slotName, 0);
}

void UBaseGameInstance::SaveGame(FString slotName)
{
	//Initializa data to save
	USaveGameData* dataToSave = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
	FVector position = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	//If there is a valid SaveGame object to use for saving
	if (dataToSave != nullptr)
	{
		//Position
		dataToSave->characterPosition = position;

		//Health
		dataToSave->health = currentHealth;

		//Buildings
		dataToSave->everyBuildMaster = SaveBuildings();

		//Save Game
		UGameplayStatics::SaveGameToSlot(dataToSave, slotName, 0);
	}
	else if (!UGameplayStatics::DoesSaveGameExist(slotName, 0))
	{
		//Create a default save file
		CreateSaveFile(slotName);
	}
}

void UBaseGameInstance::LoadGame(FString slotName)
{
	//Retrieve data to load
	USaveGameData* dataToLoad = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(slotName, 0));

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

		LoadBuildings(dataToLoad->everyBuildMaster);
	}
	else if (!UGameplayStatics::DoesSaveGameExist(slotName, 0))
	{
		//Create a default save file
		CreateSaveFile(slotName);
	}
}

TArray<FBuildings> UBaseGameInstance::SaveBuildings() {
	TArray<FBuildings> buildings;
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(World, ABuildMasterBase::StaticClass(), foundActors);
		for (AActor* Actor : foundActors)
		{
			FBuildings newStruct;
			newStruct.nameClass = Actor->GetClass()->GetPathName();
			newStruct.position = Actor->GetActorLocation();
			newStruct.rotation = Actor->GetActorRotation();
			buildings.Add(newStruct);
		}
	}

	return buildings;
}

void UBaseGameInstance::LoadBuildings(TArray<FBuildings> buildings) 
{
	UWorld* World = GetWorld();

	if (World)
	{
		FActorSpawnParameters SpawnParams;

		for (FBuildings building : buildings) 
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(building.position);
			SpawnTransform.SetRotation(FQuat::Identity);
			SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

			UClass* MyActorClass = LoadObject<UClass>(nullptr, *building.nameClass);
			if (MyActorClass)
			{
				World->SpawnActor<AActor>(MyActorClass, SpawnTransform, SpawnParams);
			}
		}
	}
}