// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameState.h"
#include "Project/GamePlay/AbilitySystem/ProjectAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Project/GamePlay/Messages/ProjectVerbMessage.h"
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

	
	// Send a message that all clients will (probably) get
	// (use only for client notifications like eliminations, server join messages, etc... that can handle being lost)
	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "GamePlay|GameStateBase")
	void MulticastMessageToClients(const FProjectVerbMessage Message);

	// Send a message that all clients will be guaranteed to get
	// (use only for client notifications that cannot handle being lost)
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "GamePlay|GameStateBase")
	void MulticastReliableMessageToClients(const FProjectVerbMessage Message);

	// Gets the server's FPS, replicated to clients
	float GetServerFPS() const;

private:
	UPROPERTY(Replicated)
	float ServerFPS;
	
	UPROPERTY(VisibleAnywhere, Category = "GamePlay|GameStateBase")
	TObjectPtr<UProjectAbilitySystemComponent> AbilitySystemComponent;
};
