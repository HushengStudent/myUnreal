// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/Framework/Core/ProjectBasePlayerController.h"
#include "ProjectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectPlayerController : public AProjectBasePlayerController
{
	GENERATED_BODY()
	
public:
	AProjectPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	
};
