#pragma once
/**
Game assets - Assignment 2
Sentry.cpp
Purpose: Class is used for the Sentry turret mechanics.
A pawnsensing component is added to the actor, which detects nearby actors. Once an actor
is in range, it will fire a raycast, which once hits, it will fire a projectile.

@author Jack Durnford
@version 2.0
*/

/* Class includes */
#include "GameFramework/Character.h"
#include "Projectile.h"
#include "SentryGun.generated.h"

UCLASS()
class PROJECTGAME_API ASentryGun : public ACharacter
{
	GENERATED_BODY()

	/* Called when the game starts or when spawned*/
	ASentryGun(const class FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

	/* Declaring of pawnsensing component */
	UPROPERTY(EditAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	/* Fires the ray trace, and fires projectile upon hit */
	void Read();

	/* Fires a debug ray */
	void RayTraceDebug(FVector STrace, FVector ETrace);

	/* Raytrace method - returns true if hit */
	bool TraceFromSelf(FHitResult& OutResult, const float TractDistance, ECollisionChannel const CollisionChannel); //FHitResult& to get address of whats hit, makes sure not null.
	void SpawnProjectile();

public: 
	/* Blueprint class - Used to spawn instance of Blueprint from C++ class */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SocketLoc)
	TSubclassOf<class AProjectile> MyItemBlueprint;

	/* Vector variable storing the location of the socket on the turret model */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SocketLoc)
		FVector SocketLoc;

	/* Rotator variable storing the rotation of the socket on the turret model */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SocketLoc)
		FRotator SocketRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SocketLoc)
	FRotator PlayerRot;

	UFUNCTION(BlueprintImplementableEvent)
		void RotateToPlayer(FRotator RotationOfPlayer);

protected:

	/* Functions which are triggered automatically when player pawn is spotted/heard */
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);

	UFUNCTION()
		void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

};
