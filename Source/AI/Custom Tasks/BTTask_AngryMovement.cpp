// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AngryMovement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_AngryMovement::UBTTask_AngryMovement()
{
	NodeName = "AngryMove";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_AngryMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();

	float DistanceToPlayer = (AIChar->GetActorLocation() - PlayerChar->GetActorLocation()).Length();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToPlayer"), DistanceToPlayer);

	if(DistanceToPlayer < RangeToPlayer)
	{
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTTask_AngryMovement::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();

	float DistanceToPlayer = (AIChar->GetActorLocation() - PlayerChar->GetActorLocation()).Length();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToPlayer"), DistanceToPlayer);
	
	OwnerComp.GetAIOwner()->MoveToActor(PlayerChar);
	
	if(DistanceToPlayer < MinRangeToPlayer)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
	else if(DistanceToPlayer > MaxRangeToPlayer)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
