// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectHealthSet.h"

#include "Net/UnrealNetwork.h"


UProjectHealthSet::UProjectHealthSet()
{
}

void UProjectHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectHealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UProjectHealthSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
}

void UProjectHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
}

bool UProjectHealthSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UProjectHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UProjectHealthSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UProjectHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UProjectHealthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UProjectHealthSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
}
