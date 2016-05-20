// Fill out your copyright notice in the Description page of Project Settings.

#include "PROJECTGAME.h"
#include "MyBTTask_ResetRouteStop.h"
#include "BotAI.h"
#include "EnemyWayPoint.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include <Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h>


EBTNodeResult::Type UMyBTTask_ResetRouteStop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	/* Check whether the AIController component exists to avoid errors */
	ABotAI* MyController = Cast<ABotAI>(OwnerComp.GetAIOwner());
	if (MyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}


	uint8 BBResetRoute = OwnerComp.GetBlackboardComponent()->GetKeyID("ResetRoute");

	//uint8 BBResetRoute = OwnerComp.GetBlackboardComponent()->GetKeyID(ResetRoute);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBResetRoute, false);

	//OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(BBResetRoute, false);



	return EBTNodeResult::Succeeded;






}




