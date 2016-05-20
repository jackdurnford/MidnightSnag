/**
Game assets - Assignment 2
BTTask_FindWayPoint.cpp
Purpose: Class used as a custom behavior tree task. By using "EBTNodeResult::Type UMyBTTask_FindWayPoint" I'm able to place
this class, as a task, onto the behavior tree.

The purpose of this class, is to get all waypoints within the map, and select a new one randomly, and set it as the new destination within blackboard.

@author Jack Durnford
@version 2.0
*/

/* Class Includes */
#include "PROJECTGAME.h"
#include "MyBTTask_FindWayPoint.h"
#include "BotAI.h"
#include "EnemyWayPoint.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UMyBTTask_FindWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

/* Check whether the AIController component exists to avoid errors */
ABotAI* MyController = Cast<ABotAI>(OwnerComp.GetAIOwner());
if (MyController == nullptr)
{
	return EBTNodeResult::Failed;
} 

/* Gets pointer to a waypoint */
AEnemyWayPoint* CurrentWaypoint = MyController->GetWaypoint();
AActor* NewWaypoint = nullptr;

/* Get all Actors of type "EnemyWayPoint" in the level, and Iterate through them */
TArray<AActor*> AllWaypoints;
UGameplayStatics::GetAllActorsOfClass(MyController, AEnemyWayPoint::StaticClass(), AllWaypoints);

/* Select one random waypoint by index */
NewWaypoint = AllWaypoints[FMath::RandRange(0, AllWaypoints.Num() - 1)];

if (NewWaypoint)
{
	/* Assign the retrieved waypoint to blackboard as the new move destination */
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), NewWaypoint);
	return EBTNodeResult::Succeeded;
}

return EBTNodeResult::Failed;


}



