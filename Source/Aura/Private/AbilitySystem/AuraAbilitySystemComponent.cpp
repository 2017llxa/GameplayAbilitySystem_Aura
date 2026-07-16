// Copyright Druid Mechanics


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	//绑定 对任何用于该能力系统组件的Effect都会响应EffectApplied（）函数
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
												const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(1,8.f,FColor::Blue,FString("EffectApplied"));

	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	// (当某个效果被应用之后 获得与该效果相关的所有Asset Tag）Broadcast Tag to the widget controller
	EffectAssetTags.Broadcast(TagContainer);
	
}
