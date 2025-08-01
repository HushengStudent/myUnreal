// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ModularPlayerState.h"
#include "Project/GamePlay/AbilitySystem/ProjectAbilitySystemComponent.h"
#include "ProjectPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectPlayerState : public AModularPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AProjectPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "GamePlay|PlayerState")
	AProjectPlayerController* GetProjectPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "GamePlay|PlayerState")
	UProjectAbilitySystemComponent* GetProjectAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;
	
	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	//~End of AActor interface

	//~APlayerState interface
	virtual void Reset() override;
	virtual void ClientInitialize(AController* C) override;
	virtual void CopyProperties(APlayerState* PlayerState) override;
	virtual void OnDeactivated() override;
	virtual void OnReactivated() override;
	//~End of APlayerState interface

	private:
	// The ability system component subobject for game-wide things (primarily gameplay cues)
	UPROPERTY(VisibleAnywhere, Category = "GamePlay|GameState")
	TObjectPtr<UProjectAbilitySystemComponent> AbilitySystemComponent;
};
