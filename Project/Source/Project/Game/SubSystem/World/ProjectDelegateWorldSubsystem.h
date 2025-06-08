// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/Game/Core/PlayerState/ProjectPlayerState.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProjectDelegateWorldSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateAdd, AProjectPlayerState*, ProjectPlayerState);

/**
 * 
 */
UCLASS()
class PROJECT_API UProjectDelegateWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateAdd OnPlayerStateAdd;
};
