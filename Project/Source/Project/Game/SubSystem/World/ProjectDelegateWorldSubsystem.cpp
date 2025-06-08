// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDelegateWorldSubsystem.h"

void UProjectDelegateWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("UProjectDelegateWorldSubsystem::Initialize"));
}

void UProjectDelegateWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Warning, TEXT("UProjectDelegateWorldSubsystem::Deinitialize"));
}

void UProjectDelegateWorldSubsystem::Tick(float DeltaTime)
{
	// 子系统每帧执行的逻辑
}

bool UProjectDelegateWorldSubsystem::IsTickable() const
{
	return true; // 始终允许 tick
}

TStatId UProjectDelegateWorldSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UProjectDelegateWorldSubsystem, STATGROUP_Tickables);
}