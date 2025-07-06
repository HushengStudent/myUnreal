// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectAttributeSet.h"

UProjectAttributeSet::UProjectAttributeSet()
{
}

UProjectAbilitySystemComponent* UProjectAttributeSet::GetProjectAbilitySystemComponent() const
{
	return Cast<UProjectAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
