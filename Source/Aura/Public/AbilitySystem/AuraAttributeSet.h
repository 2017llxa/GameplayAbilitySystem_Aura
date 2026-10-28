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

USTRUCT()
struct  FEffectProperties////储存 FGameplayEffectContextHandle 以及 Source（施加者）和 Target（承受者）相关信息。
{
	GENERATED_BODY()
	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};

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

	/*
	在游戏效果执行之后 （从Data中获取游戏组件等数据）(也增加一次最大最小限制）
	返回 FGameplayEffectContextHandle，用来提取 Source（施加者）和 Target（承受者）相关信息。
	*/
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	// Primary Attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor)

	// Vital Attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)
	
	//Secondary Attributes
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ArmorPenetration)
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitChance)
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChance)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitDamage)
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitResistance)
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration)

	// Replication callbacks
	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData OldHealth);
	
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData OldMaxHealth);

	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData OldMana);

	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData OldMaxMana);
	
	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData OldStrength);
	
	UFUNCTION()
	void OnRep_Intelligence(FGameplayAttributeData OldIntelligence);
	
	UFUNCTION()
	void OnRep_Resilience(FGameplayAttributeData OldResilience);
	
	UFUNCTION()
	void OnRep_Vigor(FGameplayAttributeData OldVigor);
	
	UFUNCTION()
	void OnRep_Armor(FGameplayAttributeData OldArmor);
	
	UFUNCTION()
	void OnRep_ArmorPenetration(FGameplayAttributeData OldArmorPenetration);
	
	UFUNCTION()
	void OnRep_BlockChance(FGameplayAttributeData OldBlockChance);
	
	UFUNCTION()
	void OnRep_CriticalHitChance(FGameplayAttributeData OldCriticalHitChance);
	
	UFUNCTION()
	void OnRep_CriticalHitDamage(FGameplayAttributeData OldCriticalHitDamage);
	
	UFUNCTION()
	void OnRep_CriticalHitResistance(FGameplayAttributeData OldCriticalHitResistance);
	
	UFUNCTION()
	void OnRep_HealthRegeneration(FGameplayAttributeData OldHealthRegeneration);
	
	UFUNCTION()
	void OnRep_ManaRegeneration(FGameplayAttributeData OldManaRegeneration);

private:
	void SetEffectPropertiesValue(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props);
};
