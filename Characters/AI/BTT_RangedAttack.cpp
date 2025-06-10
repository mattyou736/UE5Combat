// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"

EBTNodeResult::Type UBTT_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get character
	ACharacter* CharacterRef{ OwnerComp.GetAIOwner()->GetPawn<ACharacter>()};

	//crash check
	if (!IsValid(CharacterRef)) { return EBTNodeResult::Failed; }

	//play animation
	CharacterRef->PlayAnimMontage(AnimMontage);

	double RandomValue{ UKismetMathLibrary::RandomFloat()};

	if (RandomValue > Threshold) {
		Threshold = 0.9f;
		
		//get blackboard and set state
		OwnerComp.GetBlackboardComponent()
			->SetValueAsEnum(
				TEXT("CurrentState"),
				EEnemyState::Charge
			);

		//execute task for charging at player
	}
	else
	{
		Threshold -= 0.1f;
	}

	return EBTNodeResult::Succeeded;
}
