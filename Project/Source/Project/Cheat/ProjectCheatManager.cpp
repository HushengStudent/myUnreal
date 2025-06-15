// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCheatManager.h"

#include "Project/Library/ProjectGameplayStatics.h"
#include "Project/GamePlay/GameStateBase/ProjectGameStateBase.h"


void UProjectCheatManager::ProjectCheatCommand(const int32 Param1, const float Param2) const
{
	// 实现作弊功能
	//UE_LOG(LogTemp, Warning, TEXT("Cheat executed with %d and %f"), Param1, Param2);
	const AProjectGameStateBase* GameStateBase = UProjectGameplayStatics::GetProjectGameState(GetWorld());
	UE_LOG(LogTemp, Warning, TEXT("Cheat executed with %d and %f"), GameStateBase->PlayerArray.Num(), Param2);

}
