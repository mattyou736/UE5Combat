// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EStat
{
	None UMETA(DisplayName = "None Selected"),
	Health UMETA(DisplayName = "Health"),
	MaxHealth UMETA(DisplayName = "MaxHealth"),
	Stregth UMETA(DisplayName = "Stregth"),
	Stamina UMETA(DisplayName = "Stamina"),
	MaxStamina UMETA(DisplayName = "MaxStamina")
};