// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/EnemyProjectile.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyProjectile::HandleBeginOverlap(AActor* OtherActor)
{
	//cast as pawn to be able to check correct overlap
	APawn* PawnRef{
		Cast<APawn>(OtherActor)
	};


	if (!PawnRef->IsPlayerControlled()) {
		return;
	}

	UE_LOG(LogTemp, Warning,TEXT("Player hit"));
}

