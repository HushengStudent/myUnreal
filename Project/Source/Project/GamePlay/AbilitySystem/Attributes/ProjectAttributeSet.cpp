// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAttributeSet.h"

UProjectAttributeSet::UProjectAttributeSet()
{
}

UWorld* UProjectAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UProjectAbilitySystemComponent* UProjectAttributeSet::GetProjectAbilitySystemComponent() const
{
	return Cast<UProjectAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
