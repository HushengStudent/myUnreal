// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/GamePlay/AbilitySystem/Abilities/ProjectGameplayAbility.h"
#include "ProjectGameplayAbility_Reset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UProjectGameplayAbility_Reset : public UProjectGameplayAbility
{
	GENERATED_BODY()
	
public:
	UProjectGameplayAbility_Reset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};



USTRUCT(BlueprintType)
struct FProjectPlayerResetMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> OwnerPlayerState = nullptr;
};