// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameData.h"
#include "GameFramework/Character.h"
#include "BuildMasterBase.h"
#include "InteractableActor.h"
#include "ChopableActor.h"
#include "characterNPC.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UniqueItem.h"
#include "Engine/Engine.h"
#include "ImageUtils.h"
#include "LoadScreenshot.h"

UBaseGameInstance::UBaseGameInstance() 
{
	maxHealth = 100.f;
	currentHealth = maxHealth;
	maxHunger = 100.f;
	currentHunger = maxHunger;
	maxThirst = 100.f;
	currentThirst = maxThirst;
	slotToCharge = "Preloaded";
	isLoaded = false;
}

void UBaseGameInstance::Init()
{
	Super::Init();

	FWorldDelegates::OnPreWorldInitialization.AddUObject(this, &UBaseGameInstance::HandleLevelLoaded);
}

void UBaseGameInstance::HandleLevelLoaded(UWorld* World, const UWorld::InitializationValues IVS)
{
	if (World->GetMapName() == "UEDPIE_0_mainMap")
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBaseGameInstance::LoadedGame, 0.2f, false);
	}
}

void UBaseGameInstance::CreateSaveFile(FString slotName)
{
	//Create a SaveGame object and save to the default slot
	USaveGameData* dataToSave = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));
	UGameplayStatics::SaveGameToSlot(dataToSave, slotName, 0);
}

void UBaseGameInstance::CreateSaveFile(FString slotName, FVector position, float health, TArray<FBuildings> buildings)
{
	//Create a SaveGame object and save to the default slot
	USaveGameData* dataToSave = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));

	dataToSave->characterPosition = position;
	dataToSave->health = health;
	dataToSave->everyBuildMaster = buildings;

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

		//Hunger
		dataToSave->hunger = currentHunger;

		//Thirst
		dataToSave->thirst = currentThirst;

		//Buildings
		dataToSave->everyBuildMaster = SaveBuildings();

		dataToSave->everyInteractable = SaveInteractables();

		dataToSave->everyChopable = SaveChopables();

		dataToSave->inventory = SaveInventory();

		dataToSave->quantitiesInventory = SaveQuantities();

		dataToSave->everyNonPlayerCharacter = SaveNPCs();

		//Save Game
		UGameplayStatics::SaveGameToSlot(dataToSave, slotName, 0);
	}
	else if (!UGameplayStatics::DoesSaveGameExist(slotName, 0))
	{
		//Create a default save file
		CreateSaveFile(slotName, position, currentHealth, SaveBuildings());
	}

	//Take Screenshot
	SaveScreenshot(slotName);
}

void UBaseGameInstance::LoadGame(FString slotName)
{
	//Open loading map
	slotToCharge = slotName;
	UGameplayStatics::OpenLevel(this, "LoadingMap", true);
}

void UBaseGameInstance::LoadedGame()
{
	//Retrieve data to load
	USaveGameData* dataToLoad = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(slotToCharge, 0));

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

		currentHunger = dataToLoad->hunger;

		currentThirst = dataToLoad->thirst;

		LoadBuildings(dataToLoad->everyBuildMaster);

		LoadInteractables(dataToLoad->everyInteractable);

		LoadChopables(dataToLoad->everyChopable);

		LoadInventory(dataToLoad->inventory);

		LoadQuantities(dataToLoad->quantitiesInventory);
		
		LoadNPCs(dataToLoad->everyNonPlayerCharacter);

		isLoaded = true;
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

TArray<FInteractable> UBaseGameInstance::SaveInteractables()
{
	TArray<FInteractable> interactableActors;
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(World, AInteractableActor::StaticClass(), foundActors);
		for (AActor* Actor : foundActors)
		{
			FInteractable newStruct;
			newStruct.nameClass = Actor->GetClass()->GetPathName();
			newStruct.position = Actor->GetActorLocation();
			interactableActors.Add(newStruct);

		}
	}

	return interactableActors;
}

void UBaseGameInstance::LoadInteractables(TArray<FInteractable> interactableActors)
{
	UWorld* World = GetWorld();

	if (World)
	{
		FActorSpawnParameters SpawnParams;
		for (FInteractable actor : interactableActors)
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(actor.position);
			SpawnTransform.SetRotation(FQuat::Identity);
			SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

			UClass* MyActorClass = LoadObject<UClass>(nullptr, *actor.nameClass);
			if (MyActorClass)
			{
				World->SpawnActor<AActor>(MyActorClass, SpawnTransform, SpawnParams);
			}
		}
	}
}

TArray<FChopable> UBaseGameInstance::SaveChopables()
{
	TArray<FChopable> chopableActors;
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(World, AChopableActor::StaticClass(), foundActors);
		for (AActor* Actor : foundActors)
		{
			FChopable newStruct;
			newStruct.nameClass = Actor->GetClass()->GetPathName();
			newStruct.position = Actor->GetActorLocation();
			chopableActors.Add(newStruct);

		}
	}

	return chopableActors;
}

void UBaseGameInstance::LoadChopables(TArray<FChopable> chopableActors)
{
	UWorld* World = GetWorld();

	if (World)
	{
		FActorSpawnParameters SpawnParams;
		for (FChopable actor : chopableActors)
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(actor.position);
			SpawnTransform.SetRotation(FQuat::Identity);
			SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

			UClass* MyActorClass = LoadObject<UClass>(nullptr, *actor.nameClass);
			if (MyActorClass)
			{
				AActor* SpawnedActor = World->SpawnActor<AActor>(MyActorClass, SpawnTransform, SpawnParams);
			}
		}
	}
}

TArray<FSSerializedObjectData> UBaseGameInstance::SaveInventory()
{
	TArray<FSSerializedObjectData> serializedInventory;
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(World, AInventoryController::StaticClass(), foundActors);

		if (foundActors.Num() > 0)
		{
			AInventoryController* InventoryController = Cast<AInventoryController>(foundActors[0]);
			if (InventoryController)
			{
				for (const FS_objectData& ObjectData : InventoryController->inventoryData)
				{
					FSSerializedObjectData SerializedData;
					if (SerializeFSObjectData(ObjectData, SerializedData))
					{
						serializedInventory.Add(SerializedData);
					}
				}
			}
		}
	}

	return serializedInventory;
}

void UBaseGameInstance::LoadInventory(TArray<FSSerializedObjectData>& serializedInventory)
{
    UWorld* World = GetWorld();

    if (World)
    {
        TArray<AActor*> foundActors;
        UGameplayStatics::GetAllActorsOfClass(World, AInventoryController::StaticClass(), foundActors);

        if (foundActors.Num() > 0)
        {
            AInventoryController* InventoryController = Cast<AInventoryController>(foundActors[0]);
            if (InventoryController)
            {
                TArray<FS_objectData> loadedInventory;
                for (const FSSerializedObjectData& Data : serializedInventory)
                {
                    FS_objectData ObjectData;
                    if (DeserializeFSObjectData(Data, ObjectData))
                    {
                        loadedInventory.Add(ObjectData);
						if (ObjectData.Image)
						{
							FString TexturePath = ObjectData.Image->GetPathName();
						}
                    }
                }
                InventoryController->inventoryData = loadedInventory;
            }
        }
    }
}

TArray<int32> UBaseGameInstance::SaveQuantities()
{
	TArray<int32> quantities;
	TArray<UUserWidget*> WidgetInstances;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), WidgetInstances, UUniqueItem::StaticClass(), false);

	// Ahora WidgetInstances contiene todas las instancias de UUniqueItem
	for (UUserWidget* Widget : WidgetInstances)
	{
		UUniqueItem* UniqueWidgetItem = Cast<UUniqueItem>(Widget);
		if (UniqueWidgetItem)
		{
			FString WidgetName = UniqueWidgetItem->GetName();
			quantities.Add(UniqueWidgetItem->quantityItem);
		}
	}

	return quantities;
}

void UBaseGameInstance::LoadQuantities(TArray<int32> quantities)
{
	TArray<UUserWidget*> widgetInstances;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), widgetInstances, UUniqueItem::StaticClass(), false);

	TArray<UUniqueItem*> uniqueWidgets;

	// Ahora WidgetInstances contiene todas las instancias de UUniqueItem
	for (UUserWidget* widget : widgetInstances)
	{
		UUniqueItem* UniqueWidgetItem = Cast<UUniqueItem>(widget);
		if (UniqueWidgetItem)
		{
			uniqueWidgets.Add(UniqueWidgetItem);
		}
	}

	for (int32 i = 0; i < quantities.Num(); i++) 
	{
		if (uniqueWidgets.IsValidIndex(i)) 
		{
			uniqueWidgets[i]->quantityItem = quantities[i];
			uniqueWidgets[i]->SynchronizeProperties();
			UE_LOG(LogTemp, Error, TEXT("AAAAAAAAAAADDDDDDDDDDDDSSSSSSSSS: %d"), uniqueWidgets[i]->quantityItem);
		}
	}
}

bool UBaseGameInstance::DeserializeFSObjectData(const FSSerializedObjectData& SerializedData, FS_objectData& ObjectData)
{
	// Deserializar datos de texto
	ObjectData.Name = FText::FromString(SerializedData.Name);
	ObjectData.Subname = FText::FromString(SerializedData.Subname);
	ObjectData.Description = FText::FromString(SerializedData.Description);

	// Deserializar referencias a objetos y clases
	UClass* ObjectClass = FindObject<UClass>(ANY_PACKAGE, *SerializedData.ClassPath);
	if (ObjectClass != nullptr)
	{
		ObjectData.OjectClass = ObjectClass;
	}

	AActor* Object = FindObject<AActor>(ANY_PACKAGE, *SerializedData.ObjectPath);
	if (Object != nullptr)
	{
		ObjectData.Object = Object;
	}

	UTexture2D* Image = FindObject<UTexture2D>(ANY_PACKAGE, *SerializedData.ImagePath);
	if (Image != nullptr)
	{
		ObjectData.Image = Image;
	}

	UStaticMesh* StaticMesh = FindObject<UStaticMesh>(ANY_PACKAGE, *SerializedData.StaticMeshPath);
	if (StaticMesh != nullptr)
	{
		ObjectData.StaticMesh = StaticMesh;
	}

	// Deserializar cantidad máxima
	ObjectData.maxQuantity = SerializedData.MaxQuantity;

	return true;
}

bool UBaseGameInstance::SerializeFSObjectData(const FS_objectData& ObjectData, FSSerializedObjectData& SerializedData)
{
	// Serializar datos de texto
	SerializedData.Name = ObjectData.Name.ToString();
	SerializedData.Subname = ObjectData.Subname.ToString();
	SerializedData.Description = ObjectData.Description.ToString();

	// Serializar referencias a objetos y clases
	SerializedData.ClassPath = ObjectData.OjectClass ? ObjectData.OjectClass->GetPathName() : TEXT("");
	SerializedData.ObjectPath = ObjectData.Object ? ObjectData.Object->GetPathName() : TEXT("");
	SerializedData.ImagePath = ObjectData.Image ? ObjectData.Image->GetPathName() : TEXT("");
	SerializedData.StaticMeshPath = ObjectData.StaticMesh ? ObjectData.StaticMesh->GetPathName() : TEXT("");

	// Serializar cantidad máxima
	SerializedData.MaxQuantity = ObjectData.maxQuantity;

	return true;
}

TArray<FNonPlayerCharacter> UBaseGameInstance::SaveNPCs()
{
	TArray<FNonPlayerCharacter> nonPlayerCharacters;
	UWorld* World = GetWorld();

	if (World)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(World, AcharacterNPC::StaticClass(), foundActors);

		for (AActor* Actor : foundActors)
		{
			AcharacterNPC* NPC = Cast<AcharacterNPC>(Actor);
			if (NPC)
			{
				FNonPlayerCharacter newStruct;
				newStruct.nameClass = NPC->GetClass()->GetPathName();
				newStruct.position = NPC->GetActorLocation();
				newStruct.currentHealth = NPC->currentHealth;
				nonPlayerCharacters.Add(newStruct);
			}
		}
	}

	return nonPlayerCharacters;
}

void UBaseGameInstance::LoadNPCs(TArray<FNonPlayerCharacter> nonPlayerCharacters)
{
	UWorld* World = GetWorld();

	if (World)
	{
		FActorSpawnParameters SpawnParams;
		for (FNonPlayerCharacter character : nonPlayerCharacters)
		{
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(character.position);
			SpawnTransform.SetRotation(FQuat::Identity);
			SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

			UClass* MyActorClass = LoadObject<UClass>(nullptr, *character.nameClass);
			if (MyActorClass)
			{
				AActor* SpawnedActor = World->SpawnActor<AActor>(MyActorClass, SpawnTransform, SpawnParams);
				AcharacterNPC* SpawnedCharacter = Cast<AcharacterNPC>(SpawnedActor);
				if (SpawnedCharacter)
				{
					SpawnedCharacter->currentHealth = character.currentHealth;
				}
			}
		}
	}
}


void UBaseGameInstance::SaveScreenshot(FString slotName)
{
	// Get Viewport Size
	FVector2D size = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	// Create a texture to save the screenshot
	UTexture2D* textura = UTexture2D::CreateTransient(size.X, size.Y, PF_B8G8R8A8);

	// Read Window pixels
	TArray<FColor> pixels;
	pixels.SetNumUninitialized(size.X * size.Y);
	FReadSurfaceDataFlags flags;
	GEngine->GameViewport->Viewport->ReadPixels(pixels, flags, FIntRect(0, 0, size.X, size.Y));

	// Controll access to bytes
	FByteBulkData& bulkData = textura->PlatformData->Mips[0].BulkData;
	bulkData.Lock(LOCK_READ_WRITE);
	FColor* bulkDataPtr = reinterpret_cast<FColor*>(bulkData.Realloc(pixels.Num() * sizeof(FColor)));
	for (int32 i = 0; i < pixels.Num(); i++)
	{
		bulkDataPtr[i] = pixels[i];
	}
	bulkData.Unlock();

	// Update texture
	textura->UpdateResource();

	TArray<uint8> bytes;
	FImageUtils::CompressImageArray(size.X, size.Y, pixels, bytes);

	// Create Filename
	FString filename = "";
	if (slotName == "Slot1")
	{
		filename = FPaths::ProjectDir() + TEXT("Saved/Screenshots/screenshotSlot1.png");
	}
	else if (slotName == "Slot2")
	{
		filename = FPaths::ProjectDir() + TEXT("Saved/Screenshots/screenshotSlot2.png");
	}
	else if (slotName == "Slot3")
	{
		filename = FPaths::ProjectDir() + TEXT("Saved/Screenshots/screenshotSlot3.png");
	}

	// Save bytes on file
	if (!FFileHelper::SaveArrayToFile(bytes, *filename))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save screenshot to %s"), *filename);
	}
	else
	{
		for (TObjectIterator<ULoadScreenshot> It; It; ++It)
		{
			FString name = *It->GetName();
			It->ChargeScreenshot(name);
		}
	}
}

FString UBaseGameInstance::GetSaveGamePath(const FString& NombreArchivo)
{
	// Get saved path
	FString savedPath = FPaths::ProjectSavedDir();

	// Build files path
	FString completePath = savedPath + TEXT("/SaveGames/") + NombreArchivo + TEXT(".sav");

	return completePath;
}

void UBaseGameInstance::LoadLastGame()
{
	FString lastFile;
	FDateTime lastDate = FDateTime::MinValue();

	// Find last modificated file
	for (int32 i = 1; i <= 3; ++i)
	{
		FString fileName = FString::Printf(TEXT("Slot%d"), i);
		
		if (UGameplayStatics::DoesSaveGameExist(fileName, 0))
		{
			FString filePath = GetSaveGamePath(fileName);
			IFileManager& FileManager = IFileManager::Get();
			FDateTime fileDate = FileManager.GetTimeStamp(*filePath);

			// Check file date
			if (fileDate > lastDate)
			{
				lastDate = fileDate;
				slotToCharge = fileName;
			}
		}
	}
}


float UBaseGameInstance::GetCurrentHealthBySlot(FString slotName) {
	USaveGameData* dataToLoad = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
	float health = 0.f;

	if(dataToLoad)
	{
		health = dataToLoad->health;
	}

	return health;
}

float UBaseGameInstance::GetCurrentHungerBySlot(FString slotName) {
	USaveGameData* dataToLoad = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
	float hunger = 0.f;

	if (dataToLoad)
	{
		hunger = dataToLoad->hunger;
	}

	return hunger;
}

float UBaseGameInstance::GetCurrentThirstBySlot(FString slotName) {
	USaveGameData* dataToLoad = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
	float thirst = 0.f;

	if (dataToLoad)
	{
		thirst = dataToLoad->thirst;
	}

	return thirst;
}

bool UBaseGameInstance::CheckEnabledSlot(FString slotName) {
	bool enabled = false;
	USaveGameData* dataToLoad = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(slotName, 0));

	if (dataToLoad)
	{
		enabled = true;
	}

	return enabled;
}


