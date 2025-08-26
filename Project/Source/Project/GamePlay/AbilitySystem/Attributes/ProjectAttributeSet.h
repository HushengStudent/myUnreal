// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Project/GamePlay/AbilitySystem/ProjectAbilitySystemComponent.h"
#include "ProjectAttributeSet.generated.h"

// 自动生成游戏玩法属性（Gameplay Attributes）的访问器
// GAMEPLAYATTRIBUTE_PROPERTY_GETTER:生成一个静态函数,获取类的FGameplayAttribute对象
// GAMEPLAYATTRIBUTE_VALUE_GETTER:生成一个实例方法,获取属性的当前值
// GAMEPLAYATTRIBUTE_VALUE_SETTER:生成一个实例方法,设置属性的值
// GAMEPLAYATTRIBUTE_VALUE_INITTER:生成一个实例方法,初始化属性的值

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// AActor* EffectInstigator:效果的发起者（如造成伤害的玩家）
// AActor* EffectCauser:效果的引发物（如造成伤害的武器）
// const FGameplayEffectSpec* EffectSpec:游戏效果的规格说明
// float EffectMagnitude:效果的强度值（如伤害值）
// float OldValue:属性变化前的值
// float NewValue:属性变化后的新值
DECLARE_MULTICAST_DELEGATE_SixParams(FProjectAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, const FGameplayEffectSpec* /*EffectSpec*/, float /*EffectMagnitude*/, float /*OldValue*/, float /*NewValue*/);

/**
 * 
 */
UCLASS()
class PROJECT_API UProjectAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UProjectAttributeSet();

	UWorld* GetWorld() const override;
	
	UProjectAbilitySystemComponent* GetProjectAbilitySystemComponent() const;
};
