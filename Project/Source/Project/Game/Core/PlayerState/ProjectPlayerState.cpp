// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectPlayerState.h"
#include "Project/Framework/Library/ProjectGameplayStatics.h"
#include "Project/Game/Core/GameStateBase/ProjectGameStateBase.h"
#include "Project/Game/SubSystem/World/ProjectDelegateWorldSubsystem.h"


void AProjectPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if(AProjectGameStateBase* GameStateBase = UProjectGameplayStatics::GetProjectGameState<AProjectGameStateBase>(GetWorld()))
	{
		GameStateBase->PlayerArray.Add(this);
	}
	if(const UProjectDelegateWorldSubsystem* DelegateWorldSubsystem = GetWorld()->GetSubsystem<UProjectDelegateWorldSubsystem>(); DelegateWorldSubsystem && DelegateWorldSubsystem->OnPlayerStateAdd.IsBound())
	{
		DelegateWorldSubsystem->OnPlayerStateAdd.Broadcast(this);
	}
}
