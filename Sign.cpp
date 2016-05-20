// Fill out your copyright notice in the Description page of Project Settings.

#include "PROJECTGAME.h"
#include "Sign.h"


// Sets default values
ASign::ASign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

const FString ASign::GetMessage() const
{
	return Message;
}

void ASign::SetMessage(const FString NewMessage)
{
	Message = NewMessage;
}