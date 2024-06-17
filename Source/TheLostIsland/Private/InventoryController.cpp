// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryController.h"

// Sets default values
AInventoryController::AInventoryController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Asumiendo que FS_objectData tiene un constructor predeterminado adecuado
	inventoryData.Init(FS_objectData(), 21);
}

// Called when the game starts or when spawned
void AInventoryController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

