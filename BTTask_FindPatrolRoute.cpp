/**
Game assets - Assignment 2
BTTask_FindPatrolRoute.cpp
Purpose: Class used as a custom behavior tree task. By using "EBTNodeResult::Type UBTTask_FindPatrolRoute" I'm able to place 
this class, as a task, onto the behavior tree.

The purpose of this class, is to get a waypoint, and then find a random location nearby it (to add some unpredictability), and 
then set the "Target location" within the blackboard, for the enemy to move to.

@author Jack Durnford
@version 2.0
*/
#include "PROJECTGAME.h"
#include "BTTask_FindPatrolRoute.h"
#include "BotAI.h"
#include "EnemyWayPoint.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


EBTNodeResult::Type UBTTask_FindPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/* Check whether the AIController component exists to avoid errors */
	ABotAI* MyController = Cast<ABotAI>(OwnerComp.GetAIOwner());
	if (MyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	/* Gets pointer to a waypoint */
	AEnemyWayPoint* MyWaypoint = MyController->GetWaypoint();
	if (MyWaypoint)
	{
		/* Find a position that is close to the waypoint. Then, a small random to this position is added to make less predictable patrol patterns  */
		const float SearchRadius = 200.0f; //Radius to search
		const FVector SearchOrigin = MyWaypoint->GetActorLocation(); //From the location of the waypoint
		const FVector Loc = UNavigationSystem::GetRandomReachablePointInRadius(MyController, SearchOrigin, SearchRadius);
		if (Loc != FVector::ZeroVector)
		{
			/* Set the "PatrolLocation" value in the BehaviorTree variable */
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), Loc);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

