// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockonComponentActual.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Enemy.h"

// Sets default values for this component's properties
ULockonComponentActual::ULockonComponentActual()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockonComponentActual::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()-> GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
	// ...
	
}

void ULockonComponentActual::StartLockon(float Radius)
{
	FHitResult Outresult;
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FCollisionShape Sphere{ FCollisionShape::MakeSphere(Radius) };
	//tells function to ignore simple coliders of the owner
	FCollisionQueryParams IgnoreParams{
		FName{TEXT("Ignore Collision Params")},
		false,
		OwnerRef
	};

	//will return actors in specific channel using hitresult current loc and rot a col channel and a shape
	bool bHasFoundTarget{ GetWorld()->SweepSingleByChannel(Outresult, CurrentLocation, CurrentLocation, FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel1, Sphere, IgnoreParams) };
	
	if (!bHasFoundTarget) { return; }

	//check for interface
	if (!Outresult.GetActor()->Implements<UEnemy>()) { return; }

	//a target is confirmed
	CurrentTargetActor = Outresult.GetActor();

	//disable movement
	Controller->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;

	//sets new cam ofset
	SpringArmComp->TargetOffset = FVector{ 0.0,0.0,100.0 };

	//tell enemy they been locked on too
	IEnemy::Execute_OnSelect(CurrentTargetActor);

	//signal the event has ocurred
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);

	//might not be needed
	UE_LOG(LogTemp, Warning, TEXT(" Actor Detected: %s"), 
		*Outresult.GetActor()->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Lockon Started"));
}



void ULockonComponentActual::EndLockon()
{
	//tell enemy they ended being locked on too
	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	//reset target
	CurrentTargetActor = nullptr;

	//reset movement
	MovementComp->bOrientRotationToMovement = true;
	//allow rotation
	MovementComp->bUseControllerDesiredRotation = false;

	//cam reset
	SpringArmComp->TargetOffset = FVector::ZeroVector;

	//reset lookinput
	Controller->ResetIgnoreLookInput();

	//signal the event has ocurred
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponentActual::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
	{
		EndLockon();
	}
	else
	{
		StartLockon();
	}
}


// Called every frame
void ULockonComponentActual::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//check if we have target
	if (!IsValid(CurrentTargetActor)) { return; }

	//store locations in vars
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FVector TargetLocation{ CurrentTargetActor->GetActorLocation() };

	//calculate distance between player and target
	double TargetDistance{
		FVector::Distance(CurrentLocation,TargetLocation)
	};

	//too far away break lock
	if (TargetDistance >= BreakDistance) 
	{
		EndLockon();
		return;
	}

	//makes us focus just below target to tilt the cam
	TargetLocation.Z -= 125;

	//find rotation
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);

	//set new rotation to the controller by calling the function
	Controller->SetControlRotation(NewRotation);


	// ...
}

