/**
Game assets - Assignment 2
Projectile.cpp
Purpose: Class used as an empty base class for the projectiles shot by the sentry turret.

@author Jack Durnford
@version 2.0
*/

#include "PROJECTGAME.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

