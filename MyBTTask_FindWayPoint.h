/**
Game assets - Assignment 2
BTTask_FindWayPoint.h
Purpose: Class used as a custom behavior tree task. By using "EBTNodeResult::Type UMyBTTask_FindWayPoint" I'm able to place
this class, as a task, onto the behavior tree.

The purpose of this class, is to get all waypoints within the map, and select a new one randomly, and set it as the new destination within blackboard.

@author Jack Durnford
@version 2.0
*/

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_FindWayPoint.generated.h"

UCLASS()
class PROJECTGAME_API UMyBTTask_FindWayPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
