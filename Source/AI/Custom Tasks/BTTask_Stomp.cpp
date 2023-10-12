// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Stomp.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Stomp::UBTTask_Stomp()
{
	NodeName = "BigStomp";
}

EBTNodeResult::Type UBTTask_Stomp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("BigStomp"),true);
	return EBTNodeResult::Succeeded;
}

