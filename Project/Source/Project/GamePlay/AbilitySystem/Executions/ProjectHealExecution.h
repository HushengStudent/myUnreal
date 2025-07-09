// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameplayEffectExecutionCalculation.h"

#include "ProjectHealExecution.generated.h"

class UObject;


/**
 * UProjectHealExecution
 *
 *	Execution used by gameplay effects to apply healing to the health attributes.
 */
UCLASS()
class UProjectHealExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UProjectHealExecution();

protected:

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
