/**
Game assets - Assignment 2
Projectile.h
Purpose: Class used as an empty base class for the projectiles shot by the sentry turret.

@author Jack Durnford
@version 2.0
*/
#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class PROJECTGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
