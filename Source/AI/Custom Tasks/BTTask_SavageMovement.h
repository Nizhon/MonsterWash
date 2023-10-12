// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SavageMovement.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERWASH_API UBTTask_SavageMovement : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SavageMovement();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float RangeToPlayer = 0;
	
};
