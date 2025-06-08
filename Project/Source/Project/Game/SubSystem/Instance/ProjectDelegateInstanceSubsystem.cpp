// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDelegateInstanceSubsystem.h"

void UProjectDelegateInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("UProjectDelegateInstanceSubsystem::Initialize"));
}

void UProjectDelegateInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Warning, TEXT("UProjectDelegateInstanceSubsystem::Deinitialize"));
}



