// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Animations/BossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation//PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBTT_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//get value
	bool bIsReadyToCharge{ OwnerComp.GetBlackboardComponent()
		->GetValueAsBool(TEXT("IsReadyToCharge"))
	};

	if (bIsReadyToCharge) {
		OwnerComp.GetBlackboardComponent()
			->SetValueAsBool(TEXT("IsReadyToCharge"), false);

		ChargeAtPlayer();
	}

	if (!bIsfinished) { return; }
	//finish charge task
	ControllerRef->ReceiveMoveCompleted.Remove(MoveCompletedDelegate);
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
}

UBTT_ChargeAttack::UBTT_ChargeAttack()
{
	//enable tick
	bNotifyTick = true;

	MoveCompletedDelegate.BindUFunction(
		this, "HandleMoveCompleted"
	);
}

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	//define variables
	ControllerRef = OwnerComp.GetAIOwner();
	CharacterRef = ControllerRef->GetCharacter();
	Bossanim = Cast<UBossAnimInstance>
		(CharacterRef->GetMesh()->GetAnimInstance()
	);

	//set charge to true for the animation to trigger
	Bossanim->BIsCharging = true;

	OwnerComp.GetBlackboardComponent()
		->SetValueAsBool(
			TEXT("IsReadyToCharge"), false
		);
	bIsfinished = false;
	return EBTNodeResult::InProgress;
}

void UBTT_ChargeAttack::ChargeAtPlayer()
{
	//find player loc
	APawn* PlayerRef{
		GetWorld()->GetFirstPlayerController()->GetPawn()
	};
	FVector PlayerLocation{PlayerRef->GetActorLocation()};

	FAIMoveRequest MoveRequest{ PlayerLocation };

	//make it able to avoid obstacles
	MoveRequest.SetUsePathfinding(true);
	MoveRequest.SetAcceptanceRadius(AcceptableRadius);

	//initiate move request through controller
	ControllerRef->MoveTo(MoveRequest);

	//look at player when charging
	ControllerRef->SetFocus(PlayerRef);

	ControllerRef->ReceiveMoveCompleted.AddUnique(MoveCompletedDelegate);

	//get og walk speed
	OriginalWalkSpeed = CharacterRef->GetCharacterMovement()->MaxWalkSpeed;

	CharacterRef->GetCharacterMovement();
}

void UBTT_ChargeAttack::HandleMoveCompleted()
{
	Bossanim->BIsCharging = false;

	//set timer
	FTimerHandle AttackTimerHandle;

	CharacterRef->GetWorldTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&UBTT_ChargeAttack::FinishAttackTask
		,1.0f,false);

	CharacterRef->GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;
	
}

void UBTT_ChargeAttack::FinishAttackTask()
{
	bIsfinished = true;
}
