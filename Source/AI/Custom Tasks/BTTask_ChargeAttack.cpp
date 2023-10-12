// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChargeAttack.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTTask_ChargeAttack::UBTTask_ChargeAttack()
{
	NodeName = "ChargeAttack";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();

	FVector ChargePosition = AIChar->GetActorLocation();

	float distance = (AIChar->GetActorLocation() - PlayerChar->GetActorLocation()).Length();
	ChargePosition += AIChar->GetActorForwardVector() * (distance + ChargeLength);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("ChargePosition"),ChargePosition);

	FNavLocation discard;
	
	UNavigationSystemV1* navMesh = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	
	ValidPoint = navMesh->GetRandomPointInNavigableRadius(ChargePosition, 40.0f, discard);

	if(!ValidPoint)
	{
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Magenta, "Failed to charge");
		return EBTNodeResult::Failed;
	}

	return  EBTNodeResult::InProgress;
}

void UBTTask_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* AIChar = OwnerComp.GetAIOwner()->GetCharacter();

	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	FVector ChargePosition = MyBlackboard->GetValueAsVector("ChargePosition");

	float DistanceToChargeLocation = (AIChar->GetActorLocation() - ChargePosition).Length();
	
	OwnerComp.GetAIOwner()->MoveToLocation(ChargePosition);

	ChargeTimer += DeltaSeconds;
	
	if( DistanceToChargeLocation < RangeToChargeLocation )
	{
		OwnerComp.GetAIOwner()->StopMovement();
		ChargeTimer = 0;
		AIChar->bUseControllerRotationYaw = true;
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}

	if(ChargeTimer >= 2.0f)
	{
		ChargeTimer = 0;
		AIChar->bUseControllerRotationYaw = true;
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
}
