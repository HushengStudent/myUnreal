// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "ProjectCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UProjectCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Exec)
	void ProjectCheatCommand(int32 Param1, float Param2) const;
};
