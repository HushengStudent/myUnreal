// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Project/Library/ProjectGameplayStatics.h"
#include "Project/GamePlay/GameStateBase/ProjectGameStateBase.h"
#include "Project/SubSystem/World/ProjectDelegateWorldSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ProjectPlayerState)

void AProjectPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	// DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MyTeamID, SharedParams);
	// DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, MySquadID, SharedParams);

	SharedParams.Condition = ELifetimeCondition::COND_SkipOwner;
	// DOREPLIFETIME_WITH_PARAMS_FAST(ThisClass, ReplicatedViewRotation, SharedParams);

	DOREPLIFETIME(ThisClass, StatTags);	
}

void AProjectPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if(AProjectGameStateBase* GameStateBase = UProjectGameplayStatics::GetProjectGameState(GetWorld()))
	{

	}
	if(const UProjectDelegateWorldSubsystem* DelegateWorldSubsystem = GetWorld()->GetSubsystem<UProjectDelegateWorldSubsystem>(); DelegateWorldSubsystem && DelegateWorldSubsystem->OnPlayerStateAdd.IsBound())
	{
		DelegateWorldSubsystem->OnPlayerStateAdd.Broadcast(this);
	}
}

AProjectPlayerState::AProjectPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

AProjectPlayerController* AProjectPlayerState::GetProjectPlayerController() const
{
	return Cast<AProjectPlayerController>(GetOwner());
}

UAbilitySystemComponent* AProjectPlayerState::GetAbilitySystemComponent() const
{
	return GetProjectAbilitySystemComponent();
}

void AProjectPlayerState::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AProjectPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AProjectPlayerState::Reset()
{
	Super::Reset();
}

void AProjectPlayerState::ClientInitialize(AController* C)
{
	Super::ClientInitialize(C);
}

void AProjectPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
}

void AProjectPlayerState::OnDeactivated()
{
	Super::OnDeactivated();
}

void AProjectPlayerState::OnReactivated()
{
	Super::OnReactivated();
}

void AProjectPlayerState::AddStatTagStack(FGameplayTag Tag, int32 StackCount)
{
	StatTags.AddStack(Tag, StackCount);
}

void AProjectPlayerState::RemoveStatTagStack(FGameplayTag Tag, int32 StackCount)
{
	StatTags.RemoveStack(Tag, StackCount);
}

int32 AProjectPlayerState::GetStatTagStackCount(FGameplayTag Tag) const
{
	return StatTags.GetStackCount(Tag);
}

bool AProjectPlayerState::HasStatTag(FGameplayTag Tag) const
{
	return StatTags.ContainsTag(Tag);
}