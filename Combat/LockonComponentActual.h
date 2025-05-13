// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponentActual.generated.h"

//event creation
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockonComponentActual, OnUpdatedTargetDelegate,
	AActor*,NewTargetActorRef
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULockonComponentActual : public UActorComponent
{
	GENERATED_BODY()

	//ownerreference pointer
	ACharacter* OwnerRef;

	//controller pointer to disable movement and rotation
	APlayerController* Controller;

	class UCharacterMovementComponent* MovementComp;

	//var to control camera speeds
	class USpringArmComponent* SpringArmComp;

public:	
	// Sets default values for this component's properties
	ULockonComponentActual();

	//target pointer
	AActor* CurrentTargetActor;

	UPROPERTY(BlueprintAssignable);
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius = 750.0f);

	UFUNCTION(BlueprintCallable)
	void EndLockon();

	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float Radius = 750.0f);

	//distance the lockon will break on
	UPROPERTY(EditAnywhere)
	double BreakDistance{ 1000.0 };

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
