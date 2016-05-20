// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InventoryItem.h"
#include "PlayerCharacter.h"
#include "Trap_TripWire.generated.h"

UCLASS()
class PROJECTGAME_API ATrap_TripWire : public AInventoryItem
{
	GENERATED_UCLASS_BODY()

public:	
	// Sets default values for this actor's properties
	//ATrap_TripWire();

	//ATrap_TripWire(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LevelBlock)
	UStaticMeshComponent* StaticMeshComp;
	UStaticMesh* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LevelBlock)
	UStaticMeshComponent* CubeMeshComp;
	UStaticMesh* CubeMesh;

	UMaterial* CubeMaterial;
	UMaterial* BuildableMat;
	UMaterial* NotBuildableMat;

	APlayerCharacter* PlayerChar;
	ACharacter* myCharacter;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = LevelBlock)
	bool InConstruction;

	FORCEINLINE void SetupTrap(UStaticMeshComponent* Comp)
	{
		if (!Comp) return;
		//~~~~~~~~

		//Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldStatic);
	//	Comp->SetRelativeLocation(FVector(0, 0, 0));

		Comp->BodyInstance.SetInstanceNotifyRBCollision(true);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//Comp->BodyInstance.SetResponseToAllChannels(ECC_OverlapAll_Deprecated);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Camera, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Destructible, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Visibility, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Vehicle, ECR_Overlap);
		Comp->SetHiddenInGame(false);
	}

	FORCEINLINE void SetupCubee(UStaticMeshComponent* Comp)
	{
		if (!Comp) return;
		//~~~~~~~~

		//Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->BodyInstance.SetObjectType(ECC_WorldStatic);
		//	Comp->SetRelativeLocation(FVector(0, 0, 0));

		Comp->BodyInstance.SetInstanceNotifyRBCollision(true);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//Comp->BodyInstance.SetResponseToAllChannels(ECC_OverlapAll_Deprecated);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Camera, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Destructible, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Visibility, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Vehicle, ECR_Overlap);
		Comp->SetHiddenInGame(false);
	}

	FORCEINLINE void SetupCube(UStaticMeshComponent* Comp)
	{
		if (!Comp) return;
		//~~~~~~~~

		Comp->bOwnerNoSee = false;
		Comp->bCastDynamicShadow = true;
		Comp->CastShadow = true;
		Comp->SetMaterial(0, CubeMaterial);
		Comp->SetRelativeScale3D(FVector(0.54f, 0.051, 0.051));
		//Comp->SetRelativeLocation(FVector(0,0,3.6f));
		Comp->BodyInstance.SetObjectType(ECC_WorldStatic);
		Comp->BodyInstance.SetInstanceNotifyRBCollision(true);
		Comp->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//Comp->BodyInstance.SetResponseToAllChannels(ECC_OverlapAll_Deprecated);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldStatic, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Camera, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Destructible, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Visibility, ECR_Overlap);
		Comp->BodyInstance.SetResponseToChannel(ECC_Vehicle, ECR_Overlap);
		Comp->SetHiddenInGame(false);
	}

	UFUNCTION()
	void OnActorEndOverlap(class AActor * OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnActorBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

	
	
};
