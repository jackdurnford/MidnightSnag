// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_ResetRouteStop.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGAME_API UMyBTTask_ResetRouteStop : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
