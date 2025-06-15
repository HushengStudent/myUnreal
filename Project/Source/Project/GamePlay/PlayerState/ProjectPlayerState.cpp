// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectPlayerState.h"
#include "Project/Library/ProjectGameplayStatics.h"
#include "Project/GamePlay/GameStateBase/ProjectGameStateBase.h"
#include "Project/SubSystem/World/ProjectDelegateWorldSubsystem.h"


void AProjectPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if(AProjectGameStateBase* GameStateBase = Cast<AProjectGameStateBase>(UProjectGameplayStatics::GetProjectGameState(GetWorld())))
	{

	}
	if(const UProjectDelegateWorldSubsystem* DelegateWorldSubsystem = GetWorld()->GetSubsystem<UProjectDelegateWorldSubsystem>(); DelegateWorldSubsystem && DelegateWorldSubsystem->OnPlayerStateAdd.IsBound())
	{
		DelegateWorldSubsystem->OnPlayerStateAdd.Broadcast(this);
	}
}
