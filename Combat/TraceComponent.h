// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

	USkeletalMeshComponent* SkeletalComp;

	//name of socket where trace begins
	UPROPERTY(EditAnywhere)
	FName Start;
	//name of socket where trace ends
	UPROPERTY(EditAnywhere)
	FName End;
	//trace rotation
	UPROPERTY(EditAnywhere)
	FName Rotation;

	UPROPERTY(EditAnywhere)
	double BoxCollisionLength{ 30.0 };

	UPROPERTY(EditAnywhere)
	bool DebugMode{ false };

	TArray<AActor*> TargetsToIgnore;

public:	
	// Sets default values for this component's properties
	UTraceComponent();

	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking{false};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();
};
