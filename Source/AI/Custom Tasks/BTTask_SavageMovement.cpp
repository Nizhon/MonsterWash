// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SavageMovement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_SavageMovement::UBTTask_SavageMovement()
{
	NodeName = "SavageMove";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_SavageMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_SavageMovement::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();

	AIChar->bUseControllerRotationYaw = false;
	
	float DistanceToPlayer = (AIChar->GetActorLocation() - PlayerChar->GetActorLocation()).Length();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToPlayer"), DistanceToPlayer);
	
	OwnerComp.GetAIOwner()->MoveToActor(PlayerChar);

	if(DistanceToPlayer < RangeToPlayer)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		AIChar->bUseControllerRotationYaw = true;
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
