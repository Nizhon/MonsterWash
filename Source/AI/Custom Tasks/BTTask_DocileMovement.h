// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_DocileMovement.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERWASH_API UBTTask_DocileMovement : public UBTTaskNode
{
	GENERATED_BODY()
public:
    UBTTask_DocileMovement();
	
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	FVector CurrentLocation;
	FNavLocation RandomLocation;
	
	UPROPERTY(EditAnywhere)
	float SearchRadius = 800;
	float ChaseTimer = 0;
	bool FoundRandom;
};
