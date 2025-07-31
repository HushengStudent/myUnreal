// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameStateBase.h"


AProjectGameStateBase::AProjectGameStateBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AProjectGameStateBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AProjectGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AProjectGameStateBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AProjectGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AProjectGameStateBase::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
}

void AProjectGameStateBase::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
}

void AProjectGameStateBase::SeamlessTravelTransitionCheckpoint(bool bToTransitionMap)
{
	Super::SeamlessTravelTransitionCheckpoint(bToTransitionMap);
}

UAbilitySystemComponent* AProjectGameStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
