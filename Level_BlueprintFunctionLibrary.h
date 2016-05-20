// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnemySpawnPoint.h"
#include "BotCharacter.h"
#include "Level_BlueprintFunctionLibrary.generated.h"

/**  
 * 
 */
UCLASS()
class PROJECTGAME_API ULevel_BlueprintFunctionLibrary : public UActorComponent
{
	GENERATED_BODY()
	
public:
	ULevel_BlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer);

	float WaveSpawnTime;
	float WaveDelay;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning")
		TSubclassOf<class ABotCharacter> BurglarOne;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning")
		TSubclassOf<class ABotCharacter> BurglarTwo;


	//Functions
	UFUNCTION(BlueprintCallable, Category = EnemySpawn_SingleEnemy)
		 void SpawnEnemy(TSubclassOf<class ABotCharacter> &ActorToSpawn, FVector &SpawnLoc);


	UFUNCTION(BlueprintCallable, Category = EnemySpawn_SingleEnemy)
	void WaveManager();


	//UFUNCTION(BlueprintImplementableEvent, meta = (FriendlyName = "SpawnBurglar"))
		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Burglar Spawning", meta = (DisplayName = "SpawnBurglar"))
		 void SpawnBurglarFromBP();

	UFUNCTION(BlueprintCallable, Category = EnemySpawn_SingleEnemy)
		TSubclassOf<class ABotCharacter> GetBurglarSpawnType();
};

