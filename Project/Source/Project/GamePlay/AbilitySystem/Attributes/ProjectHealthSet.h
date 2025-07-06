// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/GamePlay/AbilitySystem/Attributes/ProjectAttributeSet.h"
#include "ProjectHealthSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT_API UProjectHealthSet : public UProjectAttributeSet
{
	GENERATED_BODY()
	
public:
	UProjectHealthSet();

	ATTRIBUTE_ACCESSORS(UProjectHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UProjectHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UProjectHealthSet, Healing);
	ATTRIBUTE_ACCESSORS(UProjectHealthSet, Damage);

	mutable FProjectAttributeEvent OnHealthChanged;
	mutable FProjectAttributeEvent OnMaxHealthChanged;
	//归零
	mutable FProjectAttributeEvent OnOutOfHealth;

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;
	
private:
	//角色的当前生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "GamePlay|AbilitySystem|Attributes|Health", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	//角色的最大生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "GamePlay|AbilitySystem|Attributes|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	//治疗效果的强度（通常作为临时属性）
	UPROPERTY(BlueprintReadOnly, Category="GamePlay|AbilitySystem|Attributes|Health", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Healing;
	//伤害效果的强度（通常作为临时属性）
	UPROPERTY(BlueprintReadOnly, Category="GamePlay|AbilitySystem|Attributes|Health", Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;

	// Used to track when the health reaches 0.
	bool bOutOfHealth;

	// Store the health before any changes 
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;
};
