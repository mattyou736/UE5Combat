// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LookAtPlayerComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULookAtPlayerComponent::ULookAtPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULookAtPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bCanRotate) {
		return;
	}
	AActor* OwnerRef{ GetOwner() };
	//boss loc
	FVector OwnerLocation{ OwnerRef->GetActorLocation() };
	
	//player 
	APlayerController* PlayerController{
		GetWorld()->GetFirstPlayerController()
	};

	//get player pawn
	APawn* PlayerPawn{PlayerController->GetPawn()};
	//location
	FVector PlayerLocation{ PlayerPawn->GetActorLocation() };
	//find desired rotation based on 2 locations
	FRotator DesiredRotation{
		UKismetMathLibrary::FindLookAtRotation(OwnerLocation,PlayerLocation)
	};

	FRotator CurrentRotation{ OwnerRef->GetActorRotation() };

	//dind rotation based on 2 rotations and set how fast it should rotat
	FRotator NewRotation{
		UKismetMathLibrary::RInterpTo_Constant(
			CurrentRotation,
			DesiredRotation,
			DeltaTime,
			Speed
		)
	};
	
	FRotator NewYawOnlyRotation{
		CurrentRotation.Pitch,
		NewRotation.Yaw,
		CurrentRotation.Roll
	};

	//apply rotation
	OwnerRef->SetActorRotation(NewYawOnlyRotation);
}


