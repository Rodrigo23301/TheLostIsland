// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameData.h"

USaveGameData::USaveGameData() {
	health = 100.f;
	hunger = 100.f;
	thirst = 100.f;
	characterPosition = FVector(0.f, 0.f, 0.f);
	inventory.Init(FSSerializedObjectData(), 21);
}