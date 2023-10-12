// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_JumpAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_JumpAttack::UBTTask_JumpAttack()
{
	NodeName = "JumpAttack";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_JumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();
	AIChar->bUseControllerRotationYaw = true;

	if(!OwnerComp.GetAIOwner())
	{
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Magenta, "Failed to find AIController");
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_JumpAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();

	float DistanceToPlayer = (AIChar->GetActorLocation() - PlayerChar->GetActorLocation()).Length();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToPlayer"), DistanceToPlayer);

	if(Count == 0)
	{
		OwnerComp.GetAIOwner()->MoveToActor(PlayerChar);
	}

	if(Count == 0 && DistanceToPlayer < RangeToPlayer)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		Count++;
	}

	if(Count >= 1.0f)
	{
		PlayerLocation = PlayerChar->GetActorLocation();
		OwnerComp.GetAIOwner()->MoveToLocation(PlayerLocation);
		
		JumpTimer += DeltaSeconds;
		MovementVelocity = AIChar->GetVelocity();
		
		if(MovementVelocity.Length() >= JumpSpeed)
		{
			AIChar->Jump();
		}
	}

	if(JumpTimer >= JumpSuccessTimer)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		Count = 0;
		JumpTimer = 0;
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Magenta, "Task Finished");
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
