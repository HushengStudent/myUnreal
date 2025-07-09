// Fill out your copyright notice in the Description page of Project Settings.


#include "Project/GamePlay/AbilitySystem/Abilities/ProjectGameplayAbility.h"

#include "Project/GamePlay/AbilitySystem/ProjectAbilitySystemComponent.h"
#include "Project/GamePlay/Character/ProjectCharacter.h"
#include "Project/GamePlay/PlayerController/ProjectPlayerController.h"


UProjectGameplayAbility::UProjectGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bLogCancelation = false;
}

UProjectAbilitySystemComponent* UProjectGameplayAbility::GetProjectAbilitySystemComponentFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<UProjectAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent.Get()) : nullptr);
}

AProjectPlayerController* UProjectGameplayAbility::GetProjectPlayerControllerFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<AProjectPlayerController>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

AController* UProjectGameplayAbility::GetControllerFromActorInfo() const
{
	if (CurrentActorInfo)
	{
		if (AController* PC = CurrentActorInfo->PlayerController.Get())
		{
			return PC;
		}

		// Look for a player controller or pawn in the owner chain.
		AActor* TestActor = CurrentActorInfo->OwnerActor.Get();
		while (TestActor)
		{
			if (AController* C = Cast<AController>(TestActor))
			{
				return C;
			}

			if (const APawn* Pawn = Cast<APawn>(TestActor))
			{
				return Pawn->GetController();
			}

			TestActor = TestActor->GetOwner();
		}
	}

	return nullptr;
}

AProjectCharacter* UProjectGameplayAbility::GetProjectCharacterFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<AProjectCharacter>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}
