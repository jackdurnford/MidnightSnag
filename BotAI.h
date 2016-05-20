/**
Game assets - Assignment 2
BotAI.h
Purpose: Heading file for the AI controller (BotAI.cpp). Responsible for possessing the EnemyBot character class. This class is also responsible for holding the Behavior Tree and Blackboard components, acting as an access point to update and retrieve Blackboard data. 

@author Jack Durnford
@version 2.0
*/

#pragma once // Ensures source file is included only ONCE in a single compilation

/* Includes */
#include "AIController.h"
#include "EnemyWayPoint.h"
#include "BotAI.generated.h"


UCLASS()
class PROJECTGAME_API ABotAI : public AAIController
{
	GENERATED_BODY()

	/* Constructor - Used to initialise instance variables */
	ABotAI(const class FObjectInitializer& ObjectInitializer);

	/* Pass in the Pawn to control/possess (in this case, enmemy) */
	virtual void Possess(class APawn* InPawn) override;

	/* Stores the location the enemy runs to when chasing player (used within Blackboard) */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName TargetLocKey;

	/* Stores the location enemy moves to when patrolling (used within Blackboard) */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PatrolLocKey;

	/* Stores the current waypoint object from within Blackboard */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName CurrentWaypointKey;

	/* Stores the current waypoint object from within Blackboard */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AIHitTrap;

	/* Stores the current waypoint object from within Blackboard */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AIValuableFound;

	/* Stores the current waypoint object from within Blackboard */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AILeavingHouse;

	/* Stores the current waypoint object from within Blackboard */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AILightFound;

	/* Location of Valuable */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AIValuableLocation;

	/* Location of Valuable */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AIExitLocation;
	
	/* Location of Valuable */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName AIValuableHeld;

	/* Location of Valuable */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName AITrapDelayTime;
	/* Location of Valuable */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName AITrapHitLimit;

	

public:

	/* Assign reference pointers to BB and BT components */
	UBehaviorTreeComponent* BehaviorCpt;
	UBlackboardComponent* BlackboardCpt;
	/* Pass in an enemy pawn after pawnsensing so the behavior can be updated with target location */
	void SetMoveToTarget(class APawn* InPawn);
	void SetMoveToCar(class APawn* Pawn);

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Behavior)
	bool bValuableSpotted;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Behavior)
	int32 NumOfTrapsHit;
	bool LeavingHouse;


		void ValuableSpotted(bool found);
		void ValuableLocationSet(FVector Loc);
	UFUNCTION(BlueprintCallable, Category = AIBehavior)
		void ValuableHeld(bool held);
	UFUNCTION(BlueprintCallable, Category = AIBehavior)
		void SetExitLocation(FVector loc);
	UFUNCTION(BlueprintCallable, Category = AIBehavior)
		void TrapHit(bool hit);
	UFUNCTION(BlueprintCallable, Category = AIBehavior)
		void TrapHitTime(float delay);
	UFUNCTION(BlueprintCallable, Category = AIBehavior)
		void TrapsHitExitTime();

	/* Used to get get pointer to waypoint object from Blackboard variable */
	AEnemyWayPoint* GetWaypoint();

protected:

	/* AI Variables */

	/* Store the Blackboard KeyIDs for Enemy object, and Enemy location */
	uint8 EnemyKeyID; // Object     
	uint8 CarKeyID; // Object  
	uint8 EnemyLocationID; // Vector

	/*UPROPERTY(EditAnywhere, Category = Behavior)
		bool AIHitTrap;
	UPROPERTY(EditAnywhere, Category = Behavior)
		bool AIValuableFound;
	UPROPERTY(EditAnywhere, Category = Behavior)
		bool AILeavingHouse;
	UPROPERTY(EditAnywhere, Category = Behavior)
		bool AILightFound;*/
};
