// Fill out your copyright notice in the Description page of Project Settings.


#include "Project/GamePlay/AbilitySystem/Abilities/ProjectGameplayAbility_Death.h"

#include "Project/ProjectGameplayTags.h"
#include "Project/GamePlay/AbilitySystem/ProjectAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ProjectGameplayAbility_Death)

UProjectGameplayAbility_Death::UProjectGameplayAbility_Death(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

	bAutoStartDeath = true;

	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		// Add the ability trigger tag as default to the CDO.
		FAbilityTriggerData TriggerData;
		TriggerData.TriggerTag = ProjectGameplayTags::GameplayEvent_Death;
		TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
		AbilityTriggers.Add(TriggerData);
	}
}

void UProjectGameplayAbility_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	check(ActorInfo);

	UProjectAbilitySystemComponent* ProjectASC = CastChecked<UProjectAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());

	FGameplayTagContainer AbilityTypesToIgnore;
	AbilityTypesToIgnore.AddTag(ProjectGameplayTags::Ability_Behavior_SurvivesDeath);

	// Cancel all abilities and block others from starting.
	ProjectASC->CancelAbilities(nullptr, &AbilityTypesToIgnore, this);

	SetCanBeCanceled(false);

	if (bAutoStartDeath)
	{
		StartDeath();
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UProjectGameplayAbility_Death::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	check(ActorInfo);

	// Always try to finish the death when the ability ends in case the ability doesn't.
	// This won't do anything if the death hasn't been started.
	FinishDeath();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UProjectGameplayAbility_Death::StartDeath()
{
	// if (UProjectHealthComponent* HealthComponent = UProjectHealthComponent::FindHealthComponent(GetAvatarActorFromActorInfo()))
	// {
	// 	if (HealthComponent->GetDeathState() == EProjectDeathState::NotDead)
	// 	{
	// 		HealthComponent->StartDeath();
	// 	}
	// }
}

void UProjectGameplayAbility_Death::FinishDeath()
{
	// if (UProjectHealthComponent* HealthComponent = UProjectHealthComponent::FindHealthComponent(GetAvatarActorFromActorInfo()))
	// {
	// 	if (HealthComponent->GetDeathState() == EProjectDeathState::DeathStarted)
	// 	{
	// 		HealthComponent->FinishDeath();
	// 	}
	// }
}




