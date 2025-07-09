// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/GamePlay/AbilitySystem/Attributes/ProjectAttributeSet.h"
#include "ProjectCombatSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UProjectCombatSet : public UProjectAttributeSet
{
	GENERATED_BODY()
	
public:

	UProjectCombatSet();

	ATTRIBUTE_ACCESSORS(UProjectCombatSet, BaseDamage);
	ATTRIBUTE_ACCESSORS(UProjectCombatSet, BaseHeal);

protected:

	UFUNCTION()
	void OnRep_BaseDamage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BaseHeal(const FGameplayAttributeData& OldValue);

private:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseDamage, Category = "GamePlay|AbilitySystem|Attributes|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseDamage;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseHeal, Category = "GamePlay|AbilitySystem|Attributes|Combat", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseHeal;
};