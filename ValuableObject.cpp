// Fill out your copyright notice in the Description page of Project Settings.

#include "PROJECTGAME.h"
#include "ValuableObject.h"


// Sets default values
AValuableObject::AValuableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AValuableObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AValuableObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

