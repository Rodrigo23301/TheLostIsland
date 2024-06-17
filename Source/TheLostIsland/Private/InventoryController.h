// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryController.generated.h"


/** Please add a struct description */
USTRUCT(BlueprintType)
struct FS_objectData
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Name"))
	FText Name;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Subname"))
	FText Subname;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Description"))
	FText Description;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Image", MakeStructureDefaultValue = "None"))
	TObjectPtr<UTexture2D> Image;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (DisplayName = "Object", MakeStructureDefaultValue = "None"))
	TObjectPtr<AActor> Object;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "OjectClass", MakeStructureDefaultValue = "None"))
	TObjectPtr<UClass> OjectClass;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "StaticMesh", MakeStructureDefaultValue = "None"))
	TObjectPtr<UStaticMesh> StaticMesh;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "maxQuantity", MakeStructureDefaultValue = "0"))
	int32 maxQuantity;
};



UCLASS()
class AInventoryController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	TArray<FS_objectData> inventoryData;

	UPROPERTY(BlueprintReadWrite)
	TArray<int32> quantity;

};
