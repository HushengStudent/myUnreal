// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameplayEffectExecutionCalculation.h"

#include "ProjectDamageExecution.generated.h"

class UObject;


/**
 * UProjectDamageExecution
 *
 *	Execution used by gameplay effects to apply damage to the health attributes.
 */
UCLASS()
class UProjectDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UProjectDamageExecution();

protected:

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
