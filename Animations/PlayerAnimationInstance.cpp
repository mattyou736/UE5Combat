// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimationInstance.h"

void UPlayerAnimationInstance::UpdateSpeed()
{
	//get pawn
	APawn* PawnRef{ TryGetPawnOwner() };

	//when using try functions check if they return something before use
	if (!IsValid(PawnRef)) 
	{
		return;
	}

	//get vector
	FVector Velocity{ PawnRef->GetVelocity() };

	//vector length // explicit statement of conversion
	CurrentSpeed = static_cast<float>( Velocity.Length());
}

//sets bool for animations
void UPlayerAnimationInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);

}

void UPlayerAnimationInstance::UpdateDirection()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if (!IsValid(PawnRef)) { return; }

	if (!bIsInCombat) { return; }

	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);
}
