// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemy.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONCOMBAT_API IEnemy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//specifier tells unreal this function wont be defined from interface or actor inhereting from interface
	//instead it will be defined from actors blueprint
	UFUNCTION(BlueprintImplementableEvent)
	void OnSelect();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeselect();
};
