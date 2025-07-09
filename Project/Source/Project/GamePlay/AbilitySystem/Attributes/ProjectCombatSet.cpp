// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCombatSet.h"

#include "Net/UnrealNetwork.h"


UProjectCombatSet::UProjectCombatSet()
	: BaseDamage(0.0f)
	, BaseHeal(0.0f)
{
}

void UProjectCombatSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UProjectCombatSet, BaseDamage, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectCombatSet, BaseHeal, COND_OwnerOnly, REPNOTIFY_Always);
}

void UProjectCombatSet::OnRep_BaseDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectCombatSet, BaseDamage, OldValue);
}

void UProjectCombatSet::OnRep_BaseHeal(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectCombatSet, BaseHeal, OldValue);
}
