// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_JumpAttack.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERWASH_API UBTTask_JumpAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_JumpAttack();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	FVector PlayerLocation;
	float Count = 0;

	UPROPERTY(EditAnywhere)
	float RangeToPlayer;

	UPROPERTY(EditAnywhere)
	float JumpSuccessTimer = 0.8f;
	
	float JumpTimer = 0.0f;

	UPROPERTY(EditAnywhere)
	float JumpSpeed = 400;
	
	FVector MovementVelocity;
};
