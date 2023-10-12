// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DocileMovement.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_DocileMovement::UBTTask_DocileMovement()
{
	NodeName = "DocileMove";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_DocileMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}

	CurrentLocation = OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation();
	UNavigationSystemV1* NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if(NavArea)
	{
		FoundRandom = NavArea->GetRandomReachablePointInRadius(CurrentLocation, SearchRadius, RandomLocation);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomPosition"),RandomLocation.Location);
	}
	
	if(FoundRandom)
	{
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTask_DocileMovement::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();
	
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
    FVector RandomPoint = MyBlackboard->GetValueAsVector("RandomPosition");

	FVector AICharLocation = OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("AIPosition"), AICharLocation);

	AIChar->bUseControllerRotationYaw = false;
	OwnerComp.GetAIOwner()->MoveToLocation(RandomPoint);

	float Distance = (AICharLocation - RandomPoint).Length();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("Distance"), Distance);
	
	ChaseTimer += DeltaSeconds;
	
	if( Distance < 95 )
	{
		OwnerComp.GetAIOwner()->StopMovement();
		AIChar->bUseControllerRotationYaw = true;
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
	else if (ChaseTimer >= 3)
	{
		ChaseTimer = 0;
		OwnerComp.GetAIOwner()->StopMovement();
		AIChar->bUseControllerRotationYaw = true;
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}

