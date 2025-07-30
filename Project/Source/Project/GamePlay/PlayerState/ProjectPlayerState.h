// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerState.h"
#include "ProjectPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectPlayerState : public AModularPlayerState
{
	GENERATED_BODY()
	
	
	virtual void BeginPlay() override;
	
};
