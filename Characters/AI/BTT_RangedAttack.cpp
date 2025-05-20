// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UBTT_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get character
	ACharacter* CharacterRef{ OwnerComp.GetAIOwner()->GetPawn<ACharacter>()};

	//crash check
	if (!IsValid(CharacterRef)) { return EBTNodeResult::Failed; }

	//play animation
	CharacterRef->PlayAnimMontage(AnimMontage);
	return EBTNodeResult::Succeeded;
}
