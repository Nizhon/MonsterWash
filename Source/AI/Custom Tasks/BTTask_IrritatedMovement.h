// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_IrritatedMovement.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERWASH_API UBTTask_IrritatedMovement : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_IrritatedMovement();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float RunRange = -600;
	float RunTimer = 0;

	UPROPERTY(EditAnywhere)
	float RangeToPlayerFinish = 0;

	UPROPERTY(EditAnywhere)
	float RangeToPlayerStart = 0;
};
