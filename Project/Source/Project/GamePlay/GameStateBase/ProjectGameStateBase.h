// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameState.h"
#include "Project/GamePlay/AbilitySystem/ProjectAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "ProjectGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectGameStateBase : public AModularGameStateBase, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	AProjectGameStateBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	
	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;
	//~End of AActor interface

	//~AGameStateBase interface
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
	virtual void SeamlessTravelTransitionCheckpoint(bool bToTransitionMap) override;
	//~End of AGameStateBase interface

	//~IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End of IAbilitySystemInterface

private:
	UPROPERTY(VisibleAnywhere, Category = "GamePlay|GameStateBase")
	TObjectPtr<UProjectAbilitySystemComponent> AbilitySystemComponent;
};
