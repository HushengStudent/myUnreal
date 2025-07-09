// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectHealthSet.h"
#include "ProjectAttributeSet.h"
#include "Engine/World.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Project/ProjectGameplayTags.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Damage, "Gameplay.Damage");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_DamageImmunity, "Gameplay.DamageImmunity");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_DamageSelfDestruct, "Gameplay.Damage.SelfDestruct");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_FellOutOfWorld, "Gameplay.Damage.FellOutOfWorld");
UE_DEFINE_GAMEPLAY_TAG(TAG_Lyra_Damage_Message, "Project.Damage.Message");

UProjectHealthSet::UProjectHealthSet()
	: Health(100.0f)
	, MaxHealth(100.0f)
{
	bOutOfHealth = false;
	MaxHealthBeforeAttributeChange = 0.0f;
	HealthBeforeAttributeChange = 0.0f;
}

void UProjectHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectHealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjectHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UProjectHealthSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectHealthSet, Health, OldValue);

	const float CurrentHealth = GetHealth();
	const float EstimatedMagnitude = CurrentHealth - OldValue.GetCurrentValue();
	
	OnHealthChanged.Broadcast(nullptr, nullptr, nullptr, EstimatedMagnitude, OldValue.GetCurrentValue(), CurrentHealth);

	if (!bOutOfHealth && CurrentHealth <= 0.0f)
	{
		OnOutOfHealth.Broadcast(nullptr, nullptr, nullptr, EstimatedMagnitude, OldValue.GetCurrentValue(), CurrentHealth);
	}

	bOutOfHealth = (CurrentHealth <= 0.0f);
}

void UProjectHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjectHealthSet, MaxHealth, OldValue);
	OnMaxHealthChanged.Broadcast(nullptr, nullptr, nullptr, GetMaxHealth() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMaxHealth());
}

bool UProjectHealthSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	// Handle modifying incoming normal damage
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (Data.EvaluatedData.Magnitude > 0.0f)
		{
			const bool bIsDamageFromSelfDestruct = Data.EffectSpec.GetDynamicAssetTags().HasTagExact(TAG_Gameplay_DamageSelfDestruct);

			if (Data.Target.HasMatchingGameplayTag(TAG_Gameplay_DamageImmunity) && !bIsDamageFromSelfDestruct)
			{
				// Do not take away any health.
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}

#if !UE_BUILD_SHIPPING
			// 上帝模式,没有伤害
			if (Data.Target.HasMatchingGameplayTag(ProjectGameplayTags::Cheat_GodMode) && !bIsDamageFromSelfDestruct)
			{
				// Do not take away any health.
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}
#endif
		}
	}

	// Save the current health
	HealthBeforeAttributeChange = GetHealth();
	MaxHealthBeforeAttributeChange = GetMaxHealth();

	return true;
}

void UProjectHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
// 	const bool bIsDamageFromSelfDestruct = Data.EffectSpec.GetDynamicAssetTags().HasTagExact(TAG_Gameplay_DamageSelfDestruct);
// 	float MinimumHealth = 0.0f;
// 	
// #if !UE_BUILD_SHIPPING
// 	if (!bIsDamageFromSelfDestruct &&
// 		(Data.Target.HasMatchingGameplayTag(ProjectGameplayTags::Cheat_GodMode) || Data.Target.HasMatchingGameplayTag(LyraGameplayTags::Cheat_UnlimitedHealth) ))
// 	{
// 		MinimumHealth = 1.0f;
// 	}
// #endif
//
// 	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
// 	AActor* Instigator = EffectContext.GetOriginalInstigator();
// 	AActor* Causer = EffectContext.GetEffectCauser();
//
// 	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
// 	{
// 		if (Data.EvaluatedData.Magnitude > 0.0f)
// 		{
// 			FLyraVerbMessage Message;
// 			Message.Verb = TAG_Lyra_Damage_Message;
// 			Message.Instigator = Data.EffectSpec.GetEffectContext().GetEffectCauser();
// 			Message.InstigatorTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
// 			Message.Target = GetOwningActor();
// 			Message.TargetTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();
// 			//@TODO: Fill out context tags, and any non-ability-system source/instigator tags
// 			//@TODO: Determine if it's an opposing team kill, self-own, team kill, etc...
// 			Message.Magnitude = Data.EvaluatedData.Magnitude;
//
// 			UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
// 			MessageSystem.BroadcastMessage(Message.Verb, Message);
// 		}
//
// 		// Convert into -Health and then clamp
// 		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumHealth, GetMaxHealth()));
// 		SetDamage(0.0f);
// 	}
// 	else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
// 	{
// 		// Convert into +Health and then clamo
// 		SetHealth(FMath::Clamp(GetHealth() + GetHealing(), MinimumHealth, GetMaxHealth()));
// 		SetHealing(0.0f);
// 	}
// 	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
// 	{
// 		// Clamp and fall into out of health handling below
// 		SetHealth(FMath::Clamp(GetHealth(), MinimumHealth, GetMaxHealth()));
// 	}
// 	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
// 	{
// 		// TODO clamp current health?
//
// 		// Notify on any requested max health changes
// 		OnMaxHealthChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, MaxHealthBeforeAttributeChange, GetMaxHealth());
// 	}
//
// 	// If health has actually changed activate callbacks
// 	if (GetHealth() != HealthBeforeAttributeChange)
// 	{
// 		OnHealthChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeAttributeChange, GetHealth());
// 	}
//
// 	if ((GetHealth() <= 0.0f) && !bOutOfHealth)
// 	{
// 		OnOutOfHealth.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeAttributeChange, GetHealth());
// 	}
//
// 	// Check health again in case an event above changed it.
// 	bOutOfHealth = (GetHealth() <= 0.0f);
}

void UProjectHealthSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UProjectHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UProjectHealthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UProjectHealthSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
}
