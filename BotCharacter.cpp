/**
Dynamic Assets - Task 3
BotCharacter.cpp
Purpose: Contains all of the components for Pawnsensing. Updates Blackboard through the BotAI controller.

@author Jack Durnford
@version 3.0
*/

/* My class includes */
#include "PROJECTGAME.h"
#include "BotCharacter.h"
#include "ValuableObject.h"
#include "WindUpCar.h"
#include "HUDClass.h"
#include "PlayerCharacter.h"
#include "BotAI.h"

/* AI Include */
#include "Perception/PawnSensingComponent.h"

ABotCharacter::ABotCharacter()
{
	PrimaryActorTick.bCanEverTick = true; // Allow this actor to tick each frame.

	AIControllerClass = ABotAI::StaticClass();
	AIController = Cast<ABotAI>(GetController());
	/* The sensing component to detect players by visibility checks. Modification of Pawnsensing component settings */
	PawnSensingCpt = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingCpt"));
	PawnSensingCpt->SetPeripheralVisionAngle(60.0f);
	PawnSensingCpt->SightRadius = 2000;
	PawnSensingCpt->LOSHearingThreshold = 1200;
	PawnSensingCpt->HearingThreshold = 600;
	

	/* Modification of the actors capsule component */
	GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f, false);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	/* The time in which the enemy bot stops sensing */
	SenseTimeOut = 30.0f; 




	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABotCharacter::OnHit);

}

/**
* Used to fire the pawnsensing delegate functions in order to track.
* Called when the game starts or when spawned.
*
* @param N/A.
* @return N/A.
*/
void ABotCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensingCpt)
	{
		PawnSensingCpt->OnSeePawn.AddDynamic(this, &ABotCharacter::OnSeePlayer);
		PawnSensingCpt->OnHearNoise.AddDynamic(this, &ABotCharacter::OnHearNoise);

		//bool socketLocation = GetMesh()->GetSocketLocation("SocketName");
	//	FName HeadSocketName = TEXT(Head);
		//PawnSensingCpt->AttachRootComponentToActor(this, HeadSocketName, EAttachLocation::SnapToTarget, true);
		
	}	
}

/**
* Used to check whether the last time an actor was sensed, is not beyond the timeout value, in order to prevent continuous following.
*
* @param Delta seconds.
* @return N/A.
*/
void ABotCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
 AIController = Cast<ABotAI>(GetController());

 if (HoldingValuableCode)
 {
	 this->GetCharacterMovement()->MaxWalkSpeed = 80;
 }

	/* TIMEOUT - PLAYER SENSING */
	if (bTargetSensed && (GetWorld()->TimeSeconds - TimeLastSeen) > SenseTimeOut
		&& (GetWorld()->TimeSeconds - LastHeardTime) > SenseTimeOut)
	{
		ABotAI* AIController = Cast<ABotAI>(GetController());
		if (AIController)
		{
			if (CanChangeTarget)
			{
				/* Reset target */
				bTargetSensed = false;
				PlayerHasBeenSpotted(false);
				AIController->SetMoveToTarget(nullptr);
				this->GetCharacterMovement()->MaxWalkSpeed = 90;
			}
		}
	}

	/* TIMEOUT - VALUABLE SENSING */
	if (bValuableSensed && (GetWorld()->TimeSeconds - ValuableTimeLastSeen) > SenseTimeOut
		&& (GetWorld()->TimeSeconds - ValuableLastHeardTime) > SenseTimeOut)
	{
		ABotAI* AIController = Cast<ABotAI>(GetController());
		if (AIController)
		{
			/* Reset target */
			bValuableSensed = false;
			AIController->ValuableSpotted(nullptr);
			ValuableLocation = FVector(NULL);
			AIController->ValuableLocationSet(ValuableLocation);
		}
	}

	/* TIMEOUT - VALUABLE SENSING */
	if (bCarSensed && (GetWorld()->TimeSeconds - ValuableTimeLastSeen) > SenseTimeOut
		&& (GetWorld()->TimeSeconds - ValuableLastHeardTime) > SenseTimeOut)
	{
		ABotAI* AIController = Cast<ABotAI>(GetController());
		if (AIController)
		{
			/* Reset target */
			bCarSensed = false;
			AIController->SetMoveToCar(nullptr);
			this->GetCharacterMovement()->MaxWalkSpeed = 90;
		}
	}
}

/**
* Once a player is spotted, the time it was spotted is logged, and then the Pawn spotted will be retrieved and passed onto a movement method.
*
* @param Pawn.
* @return N/A.
*/

void ABotCharacter::ResetAllTargets()
{
	ABotAI* AIController = Cast<ABotAI>(GetController());
	AIController->SetMoveToTarget(nullptr);
	AIController->ValuableSpotted(nullptr);
}

void ABotCharacter::OnSeePlayer(APawn* Pawn)
{
	if (!BurglarDisabled || !HoldingValuableCode)
	{
		TimeLastSeen = GetWorld()->GetTimeSeconds();
		ValuableTimeLastSeen = GetWorld()->GetTimeSeconds();

		/* PLAYER SENSING */
		APlayerCharacter* SensedPawn = Cast<APlayerCharacter>(Pawn);
		if (SensedPawn)
		{
			bTargetSensed = true;
			ABotAI* AIController = Cast<ABotAI>(GetController());

			if(!HoldingValuableCode)
			{
				this->GetCharacterMovement()->MaxWalkSpeed = 290;
			}

			if (AIController)
			{
				AIController->SetMoveToTarget(SensedPawn);
				PlayerHasBeenSpotted(true);
			}
			return;
		}

		AWindUpCar* CarSensed = Cast<AWindUpCar>(Pawn);
		if (CarSensed)
		{
			bCarSensed = true;
			ABotAI* AIController = Cast<ABotAI>(GetController());

			if (!HoldingValuableCode)
			{
				this->GetCharacterMovement()->MaxWalkSpeed = 290;
			}

			if (AIController)
			{
				AIController->SetMoveToCar(CarSensed);
			//	PlayerHasBeenSpotted(true);
			}
			return;
		}

		/* VALUABLE SENSING */
		AValuableObject* ValObj = Cast<AValuableObject>(Pawn);
		if (ValObj)
		{
			bValuableSensed = true;
			ABotAI* AIController = Cast<ABotAI>(GetController());
			AIController->ValuableSpotted(true);
			ValuableLocation = Pawn->GetActorLocation();
			AIController->ValuableLocationSet(ValuableLocation);
			return;
		}
	}
}

void ABotCharacter::SetEnemyTar(APlayerCharacter* SensedPwn)
{
	bValuableSensed = true;
	ABotAI* AIController = Cast<ABotAI>(GetController());
	AIController->SetMoveToTarget(SensedPwn);
}

/**
* Once a player is spotted, the time it was spotted is logged, and then the Pawn spotted will be retrieved and passed onto a movement method.
*
* @param Pawn.
* @return N/A.
*/
void ABotCharacter::OnHearNoise(APawn* Noisemaker, const FVector& Location, float Vol)
{
	if(!BurglarDisabled)
	{
		//Noise detection not implemented yet.
		TimeLastSeen = GetWorld()->GetTimeSeconds();
		bTargetSensed = true;

		ABotAI* AIController = Cast<ABotAI>(GetController());
		APlayerCharacter* SensedPawn = Cast<APlayerCharacter>(Noisemaker);
		if (AIController)
		{
			//AIController->MoveToLocation(Location);	
			PlayerHasBeenSpotted(true);
			AIController->SetMoveToTarget(SensedPawn);
		}
	}
}

/**
* Used to enable/disable the enemy character from being able to detect the Player character.
* Timer function re-enables detection after 10 seconds by running the EnableDetection function.
*
* @param True/False.
* @return N/A.
*/
void ABotCharacter::AlterDetection(bool CanAlter)
{
	if(CanAlter)
	{
		PawnSensingCpt->bEnableSensingUpdates = true;
		PawnSensingCpt->bOnlySensePlayers = true;
		PawnSensingCpt->bSeePawns = true;
		PawnSensingCpt->bHearNoises = true;
	}else
	{
		PawnSensingCpt->bEnableSensingUpdates = false;
		PawnSensingCpt->bOnlySensePlayers = false;
		PawnSensingCpt->bSeePawns = false;
		PawnSensingCpt->bHearNoises = false;
	
		if(bTargetSensed)
		{
			 InvisibilityActive = true;
			ABotAI* AIController = Cast<ABotAI>(GetController());
			AIController->StopMovement();
			bTargetSensed = false;
			PlayerHasBeenSpotted(false);
			AIController->SetMoveToTarget(nullptr);
			this->GetCharacterMovement()->MaxWalkSpeed = 90;
			AIController->StopMovement();
			
		}
		GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &ABotCharacter::EnableDetection, 13.0f, false);
	}
}

/**
* Re-enables detection after being the player character enables the invisible buff.
*
* @param Pawn.
* @return N/A.
*/
void ABotCharacter::EnableDetection()
{

	InvisibilityActive = false;
	PawnSensingCpt->bEnableSensingUpdates = true;
	PawnSensingCpt->bOnlySensePlayers = true;
	PawnSensingCpt->bSeePawns = true;
	PawnSensingCpt->bHearNoises = true;

}

/**
* Once a player is spotted, the time it was spotted is logged and behavior can be implemented (TEST).
*
* @param Pawn.
* @return N/A.
*/
void ABotCharacter::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("THIS WAS A TEST FOR FUTURE REF"));
}

void ABotCharacter::CValuableSpotted(bool found)
{
	ABotAI* AIController = Cast<ABotAI>(GetController());
	AIController->ValuableSpotted(found);
}

void ABotCharacter::CValuableLocationSet(FVector Loc)
{
	ABotAI* AIController = Cast<ABotAI>(GetController());
	AIController->ValuableLocationSet(Loc);
}

void ABotCharacter::CValuableHeld(bool held)
{
	ABotAI* AIController = Cast<ABotAI>(GetController());
	AIController->ValuableHeld(held);	
	GetCharacterMovement()->MaxWalkSpeed = 120;
	
}

void ABotCharacter::CSetExitLocation(FVector loc)
{
	ABotAI* AIController = Cast<ABotAI>(GetController());
	AIController->SetExitLocation(loc);	
}
void ABotCharacter::CTrapHit(bool hit)
{
	ABotAI* AIController = Cast<ABotAI>(GetController());
	AIController->TrapHit(hit);
}

void ABotCharacter::CTrapHitTime(float delay)
{
	ABotAI* AIController = Cast<ABotAI>(GetController());
	AIController->TrapHitTime(delay);
}
