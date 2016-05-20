// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PROJECTGAME.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryItem.generated.h"

// Item Struct.. holds all the information of the item
USTRUCT(blueprintable)
struct FInventoryItemStruct
{
	GENERATED_USTRUCT_BODY()

public:

	// Item class, used to spawn the item in the world when its dropped
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		TSubclassOf<class AInventoryItem> ItemClass;

	// Item Icon that will be displayed in the slot
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		UTexture2D* ItemImage;

	// Text that the item will display as its name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		FString ActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		bool UsableItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ItemInfo)
		FString SpawnLocTarget;

	bool operator==(FInventoryItemStruct const& Other) const
	{
		if (ItemName != Other.ItemName)
		{
			return false;
		}
		if (ItemClass != Other.ItemClass)
		{
			return false;
		}
		if (ItemImage != Other.ItemImage)
		{
			return false;
		}
		if (SpawnLocTarget != Other.SpawnLocTarget)
		{
			return false;
		}
		return true;
	}
};

/**
*5
*/
UCLASS(Blueprintable)
class PROJECTGAME_API AInventoryItem : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AInventoryItem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
		FInventoryItemStruct ItemInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
		bool bDestroyAfterUse;// Should the item actor be destroyed after it has been used?

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UsedItem"))
	void ItemUsed(class APlayerCharacter* ItemOwner, FInventoryItemStruct InventoryItem);

	void UseItem(APlayerCharacter* ItemOwner, FInventoryItemStruct InventoryItem);


	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "StartFocus"))
		bool StartFocusItem();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "EndFocus"))
		bool EndFocusItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
		FName MyItemName;

	virtual void BeginPlay() override; // Override the begin play function to implement our own method

};
