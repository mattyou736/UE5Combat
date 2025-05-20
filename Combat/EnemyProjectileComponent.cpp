// Fill out your copyright notice in the Description page of Project Settings.

/*
#include "Combat/EnemyProjectileComponent.h"

// Sets default values
AEnemyProjectileComponent::AEnemyProjectileComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyProjectileComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyProjectileComponent::SpawnProjectile(FName ComponentName, TSubclassOf<AActor> ProjectileClass)
{
	//get spawn point
	USceneComponent* SpawnPointComp{
		Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(ComponentName)) };
	//get location
	FVector SpawnLocation{ SpawnPointComp->GetComponentLocation() };
	
	//spawn actor
	GetWorld()->SpawnActor(ProjectileClass,&SpawnLocation);

}
*/
