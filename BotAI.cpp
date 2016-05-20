/**
Game assets - Assignment 2
BotAI.cpp
Purpose: Responsible for possessing the EnemyBot character class. This class is also responsible for holding the Behavior Tree and Blackboard components, acting as an access point to update and retrieve Blackboard data.

@author Jack Durnford
@version 2.0 
*/
 
/* My class includes */
#include "PROJECTGAME.h" 
#include "BotAI.h"
#include "BotCharacter.h"
#include "EnemyWayPoint.h"
 
/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


ABotAI::ABotAI(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Make Blackboard & Behavior tree components subobjects of this actor */
	BehaviorCpt = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
	BlackboardCpt = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

	/* Setting names for each FName variable, so that they can be assigned accordingly to blackboard values */
	TargetLocKey = "TargetLocation";
	PatrolLocKey = "PatrolLocation";
	CurrentWaypointKey = "CurrentWaypoint";
	AIHitTrap = "HitTrap";
	AIValuableFound = "ValuableFound";
	AILeavingHouse = "LeavingHouse";
	AILightFound = "LightFound";
	AIValuableLocation = "ValuableLocation";
	AIExitLocation = "ExitDoor";
	AIValuableHeld = "ValuableHeld";
	AITrapDelayTime = "TimeDelay";
	AITrapHitLimit = "TrapHitLimit";
}

/**
* Gets called whenever a controller (this class) possess a bot. 
* Passes the Enemy pawns object + location into the Blackboard component, so that it can be used by the behavior tree.
* Initialises Blackboard component for pawn instance, starts the behavior tree sequence.  
*
* @param Enemy bot (pawn).
* @return N/A
*/
void ABotAI::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	ABotCharacter* Bot = Cast<ABotCharacter>(InPawn); //Pointer reference to Bot character class.
	if (Bot && Bot->BotBehavior)
	{
		BlackboardCpt->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset); //Initialise the blackboard
		EnemyKeyID = BlackboardCpt->GetKeyID("Enemy");
		CarKeyID = BlackboardCpt->GetKeyID("Car");
		EnemyLocationID = BlackboardCpt->GetKeyID("Destination");
		BehaviorCpt->StartTree(*Bot->BotBehavior);
	}
}

/**
* Gets waypoint from blackboard. 
*
* @param N/A
* @return pointer to waypoint object from Blackboard variable
*/
AEnemyWayPoint* ABotAI::GetWaypoint()
{
	if (!LeavingHouse)
	{
		if (BlackboardCpt)
		{
			return Cast<AEnemyWayPoint>(BlackboardCpt->GetValueAsObject(CurrentWaypointKey));
		}
	}
	return nullptr;
}

/**
* Sets the target in blackboard for the enemy to chase after, along with its location.
*
* @param Enemy bot (pawn).
* @return N/A.
*/
void ABotAI::SetMoveToTarget(APawn* Pawn)
{
	if (!LeavingHouse)
	{
		if (BlackboardCpt)
		{
			BlackboardCpt->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, Pawn);
			if (Pawn)
			{
				BlackboardCpt->SetValueAsVector(TargetLocKey, Pawn->GetActorLocation());
			}
		}
	}
}

void ABotAI::SetMoveToCar(APawn* Pawn)
{
	if (BlackboardCpt)
	{
		if(Pawn)
		{
			if (!LeavingHouse)
			{
				BlackboardCpt->SetValue<UBlackboardKeyType_Object>(CarKeyID, Pawn);
			}
		}
	}
}

void ABotAI::ValuableSpotted(bool found)
{
	if (!LeavingHouse)
	{
		bValuableSpotted = found;
		BlackboardCpt->SetValueAsBool(AIValuableFound, bValuableSpotted);
	}
}

void ABotAI::ValuableLocationSet(FVector Loc)
{
	if(bValuableSpotted)
	{
		BlackboardCpt->SetValueAsVector(AIValuableLocation, Loc);
	}
}

void ABotAI::ValuableHeld(bool held)
{
 BlackboardCpt->SetValueAsBool(AIValuableHeld, held);

}

void ABotAI::SetExitLocation(FVector loc)
{
		BlackboardCpt->SetValueAsVector(AIExitLocation, loc);
		//AIController->SetExitLocation(FVector(-189.2, -715.4, -0.3));
}

void ABotAI::TrapHit(bool hit)
{
	BlackboardCpt->SetValueAsBool(AIHitTrap, hit);
	UE_LOG(LogTemp, Warning, TEXT("hit aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa trap"));

}

void ABotAI::TrapHitTime(float delay)
{
	BlackboardCpt->SetValueAsFloat(AITrapDelayTime, delay);
}

void ABotAI::TrapsHitExitTime()
{
	LeavingHouse = true;
		BlackboardCpt->SetValueAsBool(AITrapHitLimit, true);
}



/***********************************
*								   *
*  Methods for possible later use  *
*								   *
************************************/
/* Set a new waypoint - Keeping for later possible use 
void ABotAI::SetWaypoint(AEnemyWayPoint* NewWaypoint) {if (BlackboardCpt) {BlackboardCpt->SetValueAsObject(CurrentWaypointKeyName, NewWaypoint);}} */

