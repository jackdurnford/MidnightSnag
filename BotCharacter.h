/**
Dynamic Assets - Task 3
BotCharacter.h
Purpose: Contains all of the components for Pawnsensing. Updates Blackboard through the BotAI controller.

@author Jack Durnford
@version 3.0
*/
#pragma once

#include "GameFramework/Character.h"
#include "ValuableObject.h"
#include "HUDClass.h"
#include "BotAI.h"
#include "BotCharacter.generated.h"



UCLASS()
class PROJECTGAME_API ABotCharacter : public ACharacter
{
	GENERATED_BODY()

	

	/* The time at which the player was visually spotted */
	float TimeLastSeen;

	/* The time at which the player was heard */
	float LastHeardTime;

	/* Declares whether a target has been sensed, resets after timeout to avoid having to clear target each tick */
	bool bValuableSensed;

	/* The time at which the player was visually spotted */
	float ValuableTimeLastSeen;

	/* The time at which the player was heard */
	float ValuableLastHeardTime;

	/* Location of Valuable */
	FVector ValuableLocation;



public:
	/* Sets default values for this character's properties */
	ABotCharacter();

	UBlueprint* DoorBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AIStuff)
	bool BurglarDisabled;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AIStuff)
	bool HoldingValuableCode;

	/* Declares whether a target has been sensed, resets after timeout to avoid having to clear target each tick */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AIStuff)
		bool bTargetSensed;
	bool bCarSensed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AIStuff)
		bool InvisibilityActive;


	/* Declaring of pawnsensing component */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	class UPawnSensingComponent* PawnSensingCpt;

	/* Called when the game starts or when spawned */
	virtual void BeginPlay() override;
	
	/* Called each frame */
	virtual void Tick( float DeltaSeconds ) override;

	/* The value to clear the sensed position of detected pawn. 
	Must be higher than "Sense interval" from within PawnSense component (in editor). */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SenseTimeOut;	

	UFUNCTION(BlueprintImplementableEvent)
		void PlayerHasBeenSpotted(bool yesorno);

	UFUNCTION(BlueprintCallable, Category = AI)
	void SetEnemyTar(APlayerCharacter* SensedPwn);


	
	/* The brain of the bot is driven from this behavior tree. 
	 BT assigned to character rather than BotAI, as it can allow us to 
	 create different Bots with different behaviors, based upon same AIController */
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Behavior)
		bool CanChangeTarget;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Behavior)
	APawn* PlayerCharPawn;

	//class ValuableObject* ValuableObj;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Behavior)
	ABotAI* AIController;

	/********** TASK 3 - DYNAMIC ASSETS ************/

	/* Handle to manage the timer */
	FTimerHandle DelayHandle;

	/* Enable/disable the enemy char detecting the Player character. Called in BP. */	
	UFUNCTION(BlueprintCallable, Category = Invisibility)
	void AlterDetection(bool CanAlter);


	UFUNCTION(BlueprintCallable, Category = AI)
		void CValuableSpotted(bool found);
	UFUNCTION(BlueprintCallable, Category = AI)
		void CValuableLocationSet(FVector Loc);
	UFUNCTION(BlueprintCallable, Category = AI)
		void CValuableHeld(bool held);
	UFUNCTION(BlueprintCallable, Category = AI)
		void CSetExitLocation(FVector loc);
	UFUNCTION(BlueprintCallable, Category = AI)
		void CTrapHit(bool hit);
	UFUNCTION(BlueprintCallable, Category = AI)
		void CTrapHitTime(float delay);
	UFUNCTION(BlueprintCallable, Category = AI)
		void ResetAllTargets();





	/* Re-enables detection after AlterDetection. */
	void EnableDetection();

	/* Collision detection */
	UFUNCTION()
	void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
	

protected:

	 /* Functions which are triggered automatically when player pawn is spotted/heard */
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);
	UFUNCTION()
		void OnHearNoise(APawn* Noisemaker, const FVector& Location, float Vol);
};


