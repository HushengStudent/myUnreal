// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCheatManager.h"


void UProjectCheatManager::ProjectCheatCommand(const int32 Param1, const float Param2)
{
	// 实现作弊功能
	UE_LOG(LogTemp, Warning, TEXT("Cheat executed with %d and %f"), Param1, Param2);
}
