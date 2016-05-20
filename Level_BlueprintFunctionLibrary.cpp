// Fill out your copyright notice in the Description page of Project Settings.

#include "PROJECTGAME.h"
#include "EnemySpawnPoint.h"
#include "Level_BlueprintFunctionLibrary.h"
#include "EnemyWayPoint.h"
#include "BotCharacter.h" 

 

ULevel_BlueprintFunctionLibrary::ULevel_BlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

  
TSubclassOf<class ABotCharacter> ULevel_BlueprintFunctionLibrary::GetBurglarSpawnType()
{
	TArray<AActor* > BurglarsInTheWorld; //Storage for burglars in level REFERENCE

	TArray< TSubclassOf<class ABotCharacter> > BurlgarToSpawnArrayTemp; //Storage for burglars CLASS
	BurlgarToSpawnArrayTemp.Add(BurglarOne);
	BurlgarToSpawnArrayTemp.Add(BurglarTwo);

	UGameplayStatics::GetAllActorsOfClass(this, ABotCharacter::StaticClass(), BurglarsInTheWorld);
	
	if(BurglarsInTheWorld.Num() == 0)
	{
		return BurlgarToSpawnArrayTemp[FMath::RandRange(0, BurlgarToSpawnArrayTemp.Num() - 1)];
	}
	if(BurglarsInTheWorld.Num() < 2)
	{
		for (int i = 0; i < BurglarsInTheWorld.Num(); i++)
		{
			if(BurglarsInTheWorld[i]->GetClass() == BurglarOne)
			{
				return BurglarTwo;
			}
			
			if (BurglarsInTheWorld[i]->GetClass() != BurglarOne)
			{
				return BurglarOne;
			}
		}
	}
	
		return NULL;
}



void ULevel_BlueprintFunctionLibrary::SpawnEnemy(TSubclassOf<class ABotCharacter> &ActorToSpawn, FVector &SpawnLoc)
{
	FActorSpawnParameters SpawnParams;
	TArray<AActor* > AllSpawnpoints;

	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawnPoint::StaticClass(), AllSpawnpoints);

	int32 indexOfSpawnPoint = (FMath::RandRange(1, AllSpawnpoints.Num() - 1));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(indexOfSpawnPoint));
	//UE_LOG(LogTemp, Warning, TEXT("Rnadom number is %d"), indexOfSpawnPoint);

	//if(indexOfSpawnPoint != AllSpawnpoints.Num())
	//{
		
	//}

	if (AllSpawnpoints[indexOfSpawnPoint])
	{
		ActorToSpawn = GetBurglarSpawnType();
		SpawnLoc = AllSpawnpoints[indexOfSpawnPoint]->GetActorLocation();
	//	SpawnBurglarFromBP(GetBurglarSpawnType(), AllSpawnpoints[indexOfSpawnPoint]->GetActorLocation());
		//GetWorld()->SpawnActor<ABotCharacter>(GetBurglarSpawnType()->GetDefaultObject()->GetClass(), AllSpawnpoints[indexOfSpawnPoint]->GetActorLocation(), FRotator(0, 0, 0), SpawnParams);
	}
		//AllSpawnpoints[FMath::RandRange(0, AllSpawnpoints.Num())];
}

void ULevel_BlueprintFunctionLibrary::WaveManager()
{
		
}