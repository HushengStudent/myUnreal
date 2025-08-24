#include "Project/GamePlay/AbilitySystem/Abilities/ProjectAbilityCost_PlayerTagStack.h"

#include "Project/GamePlay/PlayerState/ProjectPlayerState.h"


UProjectAbilityCost_PlayerTagStack::UProjectAbilityCost_PlayerTagStack()
{
	Quantity.SetValue(1.0f);
}

bool UProjectAbilityCost_PlayerTagStack::CheckCost(const UProjectGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (const AController* PC = Ability->GetControllerFromActorInfo())
	{
		if (const AProjectPlayerState* PS = Cast<AProjectPlayerState>(PC->PlayerState))
		{
			const int32 AbilityLevel = Ability->GetAbilityLevel(Handle, ActorInfo);

			const float NumStacksReal = Quantity.GetValueAtLevel(AbilityLevel);
			const int32 NumStacks = FMath::TruncToInt(NumStacksReal);

			return PS->GetStatTagStackCount(Tag) >= NumStacks;
		}
	}
	return false;
}

void UProjectAbilityCost_PlayerTagStack::ApplyCost(const UProjectGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo->IsNetAuthority())
	{
		if (const AController* PC = Ability->GetControllerFromActorInfo())
		{
			if (AProjectPlayerState* PS = Cast<AProjectPlayerState>(PC->PlayerState))
			{
				const int32 AbilityLevel = Ability->GetAbilityLevel(Handle, ActorInfo);

				const float NumStacksReal = Quantity.GetValueAtLevel(AbilityLevel);
				const int32 NumStacks = FMath::TruncToInt(NumStacksReal);

				PS->RemoveStatTagStack(Tag, NumStacks);
			}
		}
	}
}