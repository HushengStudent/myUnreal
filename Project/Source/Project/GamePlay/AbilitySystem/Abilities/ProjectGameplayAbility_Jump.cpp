// Fill out your copyright notice in the Description page of Project Settings.


#include "Project/GamePlay/AbilitySystem/Abilities/ProjectGameplayAbility_Jump.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ProjectGameplayAbility_Jump)

struct FGameplayTagContainer;

UProjectGameplayAbility_Jump::UProjectGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UProjectGameplayAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return false;
	}

	const AProjectCharacter* ProjectCharacter = Cast<AProjectCharacter>(ActorInfo->AvatarActor.Get());
	if (!ProjectCharacter || !ProjectCharacter->CanJump())
	{
		return false;
	}

	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UProjectGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Stop jumping in case the ability blueprint doesn't call it.
	CharacterJumpStop();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UProjectGameplayAbility_Jump::CharacterJumpStart()
{
	if (AProjectCharacter* ProjectCharacter = GetProjectCharacterFromActorInfo())
	{
		if (ProjectCharacter->IsLocallyControlled() && !ProjectCharacter->bPressedJump)
		{
			ProjectCharacter->UnCrouch();
			ProjectCharacter->Jump();
		}
	}
}

void UProjectGameplayAbility_Jump::CharacterJumpStop()
{
	if (AProjectCharacter* ProjectCharacter = GetProjectCharacterFromActorInfo())
	{
		if (ProjectCharacter->IsLocallyControlled() && ProjectCharacter->bPressedJump)
		{
			ProjectCharacter->StopJumping();
		}
	}
}





