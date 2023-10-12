// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IrritatedMovement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_IrritatedMovement::UBTTask_IrritatedMovement()
{
	NodeName = "IrritatedMove";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_IrritatedMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	if(!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Failed;
	}
	
	RunTimer = 0;
	
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();

	float DistanceToPlayer = (AIChar->GetActorLocation() - PlayerChar->GetActorLocation()).Length();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToPlayer"), DistanceToPlayer);

	if( DistanceToPlayer < RangeToPlayerStart )
	{
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
}

void UBTTask_IrritatedMovement::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();

	FVector AICharLocation = AIChar->GetActorLocation();
	
	FRotator AILookRot = UKismetMathLibrary::FindLookAtRotation(AICharLocation, PlayerChar->GetActorLocation());

	FVector AIForWardVector = UKismetMathLibrary::GetForwardVector(AILookRot);

	FVector AIRunVector = UKismetMathLibrary::Multiply_VectorFloat(AIForWardVector, RunRange);

	FVector TempAIVector = UKismetMathLibrary::Add_VectorVector(AICharLocation, AIRunVector);

	FVector AIRunLocation = FVector(TempAIVector.X, TempAIVector.Y, AICharLocation.Z);

	RunTimer += DeltaSeconds;

	if(RunTimer >= 0.5f)
	{
		OwnerComp.GetAIOwner()->MoveToLocation(AIRunLocation);
	}

	float DistanceToPlayer = (AIChar->GetActorLocation() - PlayerChar->GetActorLocation()).Length();
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("DistanceToPlayer"), DistanceToPlayer);
	
	if(DistanceToPlayer > RangeToPlayerFinish)
	{
		OwnerComp.GetAIOwner()->StopMovement();
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
