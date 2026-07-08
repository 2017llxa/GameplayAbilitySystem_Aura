// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * UAuraAttributeSet
 * 属性集示例：生命值/最大生命值/法力值/最大法力值
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	// 正确拼写
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//在属性值改变之前执行（可做最大最小值限制）
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//在游戏效果执行之后 （从Data中获取游戏组件等数据）
	//返回 FGameplayEffectContextHandle，用来提取 Source（施加者）和 Target（承受者）相关信息。
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	

	// Attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	UPROPERTY(ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	UPROPERTY(ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	// Replication callbacks
	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData OldMaxHealth);

	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData OldMana);

	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData OldMaxMana);
};
