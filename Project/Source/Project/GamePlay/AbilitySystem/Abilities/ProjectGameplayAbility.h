// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectAbilityCost.h"
#include "Abilities/GameplayAbility.h"
#include "Project/GamePlay/Character/ProjectCharacter.h"
#include "Project/GamePlay/PlayerController/ProjectPlayerController.h"
#include "ProjectGameplayAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, HideCategories = Input, Meta = (ShortTooltip = "The base gameplay ability class used by this project."))
class PROJECT_API UProjectGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend class UProjectAbilitySystemComponent;

public:

	UProjectGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Project|GamePlay|AbilitySystem|Abilities")
	UProjectAbilitySystemComponent* GetProjectAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Project|GamePlay|AbilitySystem|Abilities")
	AProjectPlayerController* GetProjectPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Project|GamePlay|AbilitySystem|Abilities")
	AController* GetControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Project|GamePlay|AbilitySystem|Abilities")
	AProjectCharacter* GetProjectCharacterFromActorInfo() const;

	
protected:

	// Additional costs that must be paid to activate this ability
	UPROPERTY(EditDefaultsOnly, Instanced, Category = Costs)
	TArray<TObjectPtr<UProjectAbilityCost>> AdditionalCosts;

	// Map of failure tags to simple error messages
	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	TMap<FGameplayTag, FText> FailureTagToUserFacingMessages;

	// Map of failure tags to anim montages that should be played with them
	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	TMap<FGameplayTag, TObjectPtr<UAnimMontage>> FailureTagToAnimMontage;

	// If true, extra information should be logged when this ability is canceled. This is temporary, used for tracking a bug.
	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	bool bLogCancelation;
};
