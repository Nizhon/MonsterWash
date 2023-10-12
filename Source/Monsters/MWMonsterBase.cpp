 //Fill out your copyright notice in the Description page of Project Settings.


#include "MWMonsterBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

 // Sets default values
AMWMonsterBase::AMWMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AMWMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	TierdTimer = 0.0f;
	
}

// Called every frame
void AMWMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AActor* Monster = GetOwner();
	AAIController* MonsterAI = UAIBlueprintHelperLibrary::GetAIController(Monster);

	
	MonsterState = MonsterAI->GetBlackboardComponent()->GetValueAsEnum("MonsterState");

	if(MonsterState == 0)
	{
		Energy -= (DeltaTime * 0.0f);
	}

	if(MonsterState == 1)
	{
		Energy -= (DeltaTime * 1.0f);
	}

	if(MonsterState == 2)
	{
		Energy -= (DeltaTime * 1.5f);
	}

	if(MonsterState == 3)
	{
		Energy -= (DeltaTime * 2.0f);
	}

	if(MonsterState == 4 && Tierd == true)
	{
		TierdTimer += DeltaTime;
		MonsterAI->GetBlackboardComponent()->SetValueAsFloat("TierdTimer", TierdTimer);
		Anger = 0;
		if(TierdTimer >= 10.0f)
		{
			Tierd = false;
			Energy = 200.0f;
			TierdTimer = 0.0f;
			MonsterAI->GetBlackboardComponent()->SetValueAsBool("Tierd", false);
			MonsterAI->GetBlackboardComponent()->SetValueAsEnum("MonsterState", 1);
		}
	}

	if(Energy <= 0 && Tierd == false)
	{
		Tierd = true;
		MonsterAI->StopMovement();
		MonsterAI->GetBlackboardComponent()->SetValueAsBool("Tierd", true);
		MonsterAI->GetBlackboardComponent()->SetValueAsEnum("MonsterState", 4);
	}
}
