// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UPlayerAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	//we define it like this to avoid c++ its type conversion therefor we use direct initialization
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed{ 0.0f };

	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInCombat{ false };
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDirection{ 0.0f };

public:

	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor* NewTargetActorRef);
	UFUNCTION(BlueprintCallable)
	void UpdateDirection();
};
