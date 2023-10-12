// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MWAIController.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERWASH_API AMWAIController : public AAIController
{
	GENERATED_BODY()
	
public:

    	
protected:
    	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};
