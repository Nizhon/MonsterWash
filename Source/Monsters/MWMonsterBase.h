// Fill out your copyright notice in the Description page of Project Settings.
//Weapons are going to have these outlining stats: 
//Cleaning rate - how quickly dirt is removed 
//Anger rate - how much Aggravation accumulates per ammo fired
//Range - How far the weapon firing reaches
//Area of effect/ size - Size of the area covered by the shot
//Ammunition count - How much shooty shoot we can do
//	Ammunition usage/ firerate - How quickly we can’t do the shooty shoot anymore :(
//	Refill time? - If we need it, how long a reload takes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MWMonsterBase.generated.h"

UCLASS()
class MONSTERWASH_API AMWMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMWMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	

	float MonsterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Energy = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TierdTimer = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Tierd = false;

};
