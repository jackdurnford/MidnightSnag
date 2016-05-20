// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "PROJECTGAME.h"
#include "InventoryItem.h"
#include "PlayerCharacter.h"


AInventoryItem::AInventoryItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();

	
}

void AInventoryItem::UseItem(APlayerCharacter* ItemOwner, FInventoryItemStruct InventoryItem)
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	ItemUsed(ItemOwner, InventoryItem); // Call the blueprint event
}




