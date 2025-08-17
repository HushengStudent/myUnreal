// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameStateBase.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ProjectGameStateBase)

extern ENGINE_API float GAverageFPS;

AProjectGameStateBase::AProjectGameStateBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ServerFPS = 0.0f;
}

void AProjectGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ServerFPS);
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

	if (GetLocalRole() == ROLE_Authority)
	{
		ServerFPS = GAverageFPS;
	}
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

float AProjectGameStateBase::GetServerFPS() const
{
	return ServerFPS;
}

void AProjectGameStateBase::MulticastReliableMessageToClients_Implementation(const FProjectVerbMessage Message)
{
	MulticastMessageToClients_Implementation(Message);
}

void AProjectGameStateBase::MulticastMessageToClients_Implementation(const FProjectVerbMessage Message)
{
	if (GetNetMode() == NM_Client)
	{
		UGameplayMessageSubsystem::Get(this).BroadcastMessage(Message.Verb, Message);
	}
}
