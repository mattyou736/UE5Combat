// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerActionsComponent::UPlayerActionsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
	//returns move comp
	MovementComp = CharacterRef->GetCharacterMovement();

	if (!CharacterRef->Implements<UMainPlayer>()) { return; }

	//update var
	IPlayerRef = Cast<IMainPlayer>(CharacterRef);

	if (IPlayerRef) {
		UE_LOG(LogTemp, Warning, TEXT("CAST Suces"));
	}
	else if(!IPlayerRef) {
		UE_LOG(LogTemp, Warning, TEXT("CAST fail"));
	}
	
}


// Called every frame
void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerActionsComponent::Sprint()
{
	//check stam
	if (!IPlayerRef->HasEnoughStamina(SprintCost)) { 
		Walk();
		return;
	}

	//check if player is moving in a tolarance
	if (MovementComp->Velocity.Equals(FVector::ZeroVector,1)) { return; }


	MovementComp->MaxWalkSpeed = SprintSpeed;

	OnSprintDelegate.Broadcast(SprintCost);
}

void UPlayerActionsComponent::Walk()
{
	MovementComp->MaxWalkSpeed = WalkSpeed;
}

