// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Stomp.generated.h"

/**
 * 
 */

UCLASS()
class MONSTERWASH_API UBTTask_Stomp : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Stomp();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
