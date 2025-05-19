// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/EnemyProjectileComponentActual.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UEnemyProjectileComponentActual::UEnemyProjectileComponentActual()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyProjectileComponentActual::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyProjectileComponentActual::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyProjectileComponentActual::SpawnProjectile(FName ComponentName, TSubclassOf<AActor> ProjectileClass)
{
	//get spawn point
	USceneComponent* SpawnPointComp{
		Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(ComponentName)) };
	//get location
	FVector SpawnLocation{ SpawnPointComp->GetComponentLocation() };

	//find player
	FVector PlayerLocation{ GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() };

	FRotator SpawnRotation{
		UKismetMathLibrary::FindLookAtRotation(
		SpawnLocation,PlayerLocation
		)
	};

	//spawn actor
	GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation,&SpawnRotation);

}


