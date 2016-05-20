/**
Game assets - Assignment 2
BTTask_FindPatrolRoute.h
Purpose: Class used as a custom behavior tree task. By using "EBTNodeResult::Type UBTTask_FindPatrolRoute" I'm able to place
this class, as a task, onto the behavior tree.

The purpose of this class, is to get a waypoint, and then find a random location nearby it (to add some unpredictability), and
then set the "Target location" within the blackboard, for the enemy to move to.

@author Jack Durnford
@version 2.0
*/

#pragma once

/* Includes */
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPatrolRoute.generated.h"

UCLASS()
class PROJECTGAME_API UBTTask_FindPatrolRoute : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
