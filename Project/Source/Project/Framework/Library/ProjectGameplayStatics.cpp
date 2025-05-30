// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGameplayStatics.h"

AProjectBaseGameStateBase* UProjectGameplayStatics::GetProjectGameState(const UObject* WorldContextObject)
{
	return GetProjectGameState<AProjectBaseGameStateBase>(WorldContextObject);
}

AProjectBaseGameMode* UProjectGameplayStatics::GetProjectGameMode(const UObject* WorldContextObject)
{
	return GetProjectGameMode<AProjectBaseGameMode>(WorldContextObject);
}

AProjectBasePlayerController* UProjectGameplayStatics::GetFirstProjectPlayerController(const UObject* WorldContextObject)
{
	return GetFirstProjectPlayerController<AProjectBasePlayerController>(WorldContextObject);
}

AProjectBasePlayerState* UProjectGameplayStatics::GetFirstProjectPlayerState(const UObject* WorldContextObject)
{
	return GetFirstProjectPlayerState<AProjectBasePlayerState>(WorldContextObject);
}

AProjectBaseCharacter* UProjectGameplayStatics::GetFirstProjectCharacter(const UObject* WorldContextObject)
{
	return GetFirstProjectCharacter<AProjectBaseCharacter>(WorldContextObject);
}
