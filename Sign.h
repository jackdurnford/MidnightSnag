// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Sign.generated.h"

UCLASS()
class PROJECTGAME_API ASign : public AActor
{
	GENERATED_BODY()

	

	UFUNCTION(BlueprintCallable, Category = Modifiers)
	void SetMessage(const FString NewMessage);

protected: 
	UPROPERTY(EditAnywhere, Category = Messages)
	FString Message;

	

public:	

	UFUNCTION(BlueprintCallable, Category = Accessors)
		const FString GetMessage() const;

	// Sets default values for this actor's properties
	ASign();
};
