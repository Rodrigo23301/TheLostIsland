// Fill out your copyright notice in the Description page of Project Settings.


#include "characterNPC.h"

// Sets default values
AcharacterNPC::AcharacterNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentHealth = 100;
}

// Called when the game starts or when spawned
void AcharacterNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AcharacterNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AcharacterNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

