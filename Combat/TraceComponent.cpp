// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/TraceComponent.h"
//to draw debug shapes
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Color.h"
#include "Interfaces/Fighter.h"
#include "Engine/DamageEvents.h"


// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsAttacking)
	{
		return;
	}

	//get start loc
	FVector StartSocketLocation{ SkeletalComp->GetSocketLocation(Start) };
	//get end loc
	FVector EndSocketLocation{ SkeletalComp->GetSocketLocation(End) };
	//get rotation
	FQuat ShapRotation{ SkeletalComp->GetSocketQuaternion(Rotation) };

	//define results Tarray comes with extra functions
	TArray<FHitResult> OutResults;

	//calculate distance in the weapon
	double WeaponDistance{
		FVector::Distance(StartSocketLocation,EndSocketLocation)
	};

	FVector BoxHalfExtend{
		BoxCollisionLength,BoxCollisionLength,WeaponDistance
	};

	BoxHalfExtend /= 2;

	//create trace shape
	FCollisionShape Box{
		FCollisionShape::MakeBox(BoxHalfExtend)
	};

	//ignore owner of attack
	FCollisionQueryParams IgnoreParams{
		FName{TEXT("Ignore Params")},
		false,
		GetOwner()
	};

	//find all targets based on the game trace channel i made in unreal
	bool BHasFoundTargets = GetWorld()->SweepMultiByChannel(
		OutResults,
		StartSocketLocation,
		EndSocketLocation,
		ShapRotation,
		ECollisionChannel::ECC_GameTraceChannel1,
		Box,
		IgnoreParams
	);

	if (DebugMode) {
		FVector CenterPoint{
			UKismetMathLibrary::VLerp(StartSocketLocation,EndSocketLocation,0.5f)
		};

		UKismetSystemLibrary::DrawDebugBox(
			GetWorld(),
			CenterPoint,
			Box.GetExtent(),
			BHasFoundTargets ? FLinearColor::Green : FLinearColor::Red,//changes color based on bool
			ShapRotation.Rotator(),//converts quat to rotation
			1.0f,2.0f
		);

		
	}

	//if no results return
	if (OutResults.Num() == 0) {
		return;
	}

	float CharacterDamage{ 0.0f };

	IFighter* FighterRef{ Cast<IFighter>(GetOwner()) };

	if (FighterRef) {
		CharacterDamage = FighterRef->GetDamage();
	}

	FDamageEvent TargetAttackedEvent;

	//apply damage loop
	//const tels c++ we wont modify array // & will reference the value not copy it for optimization sake
	for(const FHitResult& Hit: OutResults)
	{
		AActor* TargetActor{ Hit.GetActor() };

		if (TargetsToIgnore.Contains(TargetActor)) { continue; }

		//take damage
		TargetActor->TakeDamage(
			CharacterDamage,
			TargetAttackedEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner()
		);

		//makes sure we dont add doubles
		TargetsToIgnore.AddUnique(TargetActor);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Damage: %f"),CharacterDamage);
}

void UTraceComponent::HandleResetAttack()
{
	TargetsToIgnore.Empty();
}

