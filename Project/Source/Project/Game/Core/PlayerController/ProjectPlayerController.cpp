// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectPlayerController.h"

#include "Project/Game/Cheat/ProjectCheatManager.h"


AProjectPlayerController::AProjectPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void AProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	CheatClass = UProjectCheatManager::StaticClass();
	
#if !UE_BUILD_SHIPPING
	EnableCheats();
#endif
	
}


