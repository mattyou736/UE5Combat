// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/EnemyProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

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
	
	FTimerHandle DeathTimerHandle{};

	GetWorldTimerManager().SetTimer(
		DeathTimerHandle,
		this,
		&AEnemyProjectile::DestroyProjectile,
		DeathTimer
	);
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

	//grab particle comp
	FindComponentByClass<UParticleSystemComponent>()
		->SetTemplate(HitTemplate);

	//stop projectile movement
	FindComponentByClass<UProjectileMovementComponent>()
		->StopMovementImmediately();

	//setting up timer
	FTimerHandle DeathTimerHandle{};

	GetWorldTimerManager().SetTimer(
		DeathTimerHandle,
		this,
		&AEnemyProjectile::DestroyProjectile,
		0.5f
	);
	//disable colision
	FindComponentByClass<USphereComponent>()
		->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	//projectile event ref
	FDamageEvent ProjectileAttackEvent{};

	//taking damage
	PawnRef->TakeDamage(
		Damage,
		ProjectileAttackEvent,
		PawnRef->GetController(),
		this
	);
}

//destroy actor
void AEnemyProjectile::DestroyProjectile()
{
	Destroy();
}

