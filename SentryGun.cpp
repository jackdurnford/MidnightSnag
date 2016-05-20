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
#include "PROJECTGAME.h"
#include "GameFramework/Character.h"
#include "SentryGun.h"
#include "Projectile.h"

/* AI Include */
#include "Perception/PawnSensingComponent.h"


ASentryGun::ASentryGun(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Get item from Blueprint, and assign it to variable for use within this class */
//	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_MyProjectile.BP_MyProjectile'"));
//	if (ItemBlueprint.Object)
//	{
//		MyItemBlueprint = static_cast<UClass*>(ItemBlueprint.Object->GeneratedClass);
//	}

	/* Our sensing component to detect players by visibility and noise checks. */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(60.0f);
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->LOSHearingThreshold = 1200;
}

/**
*	Used to fire the pawnsensing delegate functions in order to track.
*	Called when the game starts or when spawned.
*
*	@param n/a
*	@return n/a
**/
void ASentryGun::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ASentryGun::OnSeePlayer);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &ASentryGun::OnHearNoise);
	}
}

/**
*	Used to fire the pawnsensing delegate functions in order to track.
*	Called when the game starts or when spawned. Fires the Read method below, upon spotting a target.
*
*	@param n/a
*	@return n/a
**/
void ASentryGun::OnSeePlayer(APawn* Pawn)
{
	FVector SentryLoc = GetActorLocation();
	FVector EnemyLoc = Pawn->GetActorLocation();
	Read();

	FRotator PlayerRot = FRotationMatrix::MakeFromX(EnemyLoc - SentryLoc).Rotator();
	RotateToPlayer(PlayerRot);
	//SetActorRelativeRotation(PlayerRot, true);
}

/**
*	Runs the ray trace method, firing a ray out infront of the Sentry upon detecting an actor.
*
*	@param n/a
*	@return n/a
**/
void ASentryGun::Read()
{
	FHitResult HitResult(EForceInit::ForceInit);
	
	bool bTraceSuccess = TraceFromSelf(HitResult, 3000.0f, ECollisionChannel::ECC_EngineTraceChannel1);
	if (bTraceSuccess)
	{
		AActor* const HitActor = HitResult.GetActor(); //Get actor collided with. Get actor from hitresult
		if (HitActor) //Check if hit result exists (Safety)
		{ 
			SpawnProjectile(); 
		}
	}
}

/*
*	 Function to draw the ray trace.
*	 For debugging purposes.
*/
void ASentryGun::RayTraceDebug(FVector STrace, FVector ETrace)
{
	DrawDebugLine(GetWorld(), STrace, ETrace, FColor(255, 0, 0), false, -1, 0, 12.333);
}

/**
*	Get location and rotation of camera. Sets players view point to camera location and rotation.
*	Sets where the trace will start, which direction, and where it ends. Traceparms setup to return details of whats collided.
*	Traces a ray against the world, returning the first blocking hit.
*
*	@params location to store hit info, distance of trace ray, the collision channel
*	@return return the hit actor.
**/
bool ASentryGun::TraceFromSelf(FHitResult& OutResult, const float TraceDistance, ECollisionChannel const CollisionChannel)
{
	if (Controller)
	{
		FVector LocationLoc; //location and rotation of camera variables
		FRotator RotationRot;
		Controller->GetPlayerViewPoint(LocationLoc, RotationRot); //Location to cast ray (from player)

		FVector const StartTrace = LocationLoc;
		FVector const ShootDirection = RotationRot.Vector();
		FVector const EndTrace = StartTrace + ShootDirection * TraceDistance;

		FCollisionQueryParams TraceParms(FName(TEXT("TraceFromSelf")), true, this); //returns what is collided


		bool bHitReturned = false; //to determine if anything hit
		UWorld* const World = GetWorld();

		if (World)
		{
			bHitReturned = World->LineTraceSingleByChannel(OutResult, StartTrace, EndTrace, CollisionChannel, TraceParms); 
			RayTraceDebug(StartTrace, EndTrace);
		}

		TraceParms.bTraceAsyncScene = true; //Whether we should perform the trace in the asynchronous scene.Default is false.
		TraceParms.bReturnPhysicalMaterial = false;  //Only fill in the PhysMaterial field 
		TraceParms.bTraceComplex = true; //Whether we should trace against complex collision

		return bHitReturned;
	}
	return false; //if there is no controller, nothing traced.
}

/**
*	Function to spawn the blueprint actor "Projectile", from the SentryGun, into the game world.
*	The projectile spawns at particular locations on the 3d model, called "Sockets". 
*	The projectile blueprint is sending its location to the variables "SocketLoc" and "SocketRotation"
*	within this class.
*
*	@params n/a
*	@return void
**/
void ASentryGun::SpawnProjectile()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		World->SpawnActor<AProjectile>(MyItemBlueprint, SocketLoc, SocketRotation, SpawnParams);
	}
}

void ASentryGun::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	//Not currently used.
}

