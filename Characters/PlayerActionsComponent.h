// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"

//first arg name of event second vaiable for storing event info
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature,
	UPlayerActionsComponent, OnSprintDelegate,
	float, Cost
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

	//used for grabbing playermovement and velovcity
	ACharacter* CharacterRef;

	//responsible for all player actions
	class IMainPlayer* IPlayerRef;

	class UCharacterMovementComponent* MovementComp;

	//define var for stam cost
	UPROPERTY(EditAnywhere)
	float SprintCost{ 0.1 };

	//define speed
	UPROPERTY(EditAnywhere)
	float SprintSpeed{ 1000.0f };

	//og speed
	UPROPERTY(EditAnywhere)
	float WalkSpeed{ 500.0f };

public:	
	// Sets default values for this component's properties
	UPlayerActionsComponent();

	UPROPERTY(BlueprintAssignable)
	FOnSprintSignature OnSprintDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable)
	void Walk();
};
