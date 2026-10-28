// Copyright Druid Mechanics


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::CallBacksToDepends()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data)
				{
					OnHealthChanged.Broadcast(Data.NewValue);
				});
	//.AddUObject(this,&UOverlayWidgetController::HealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data)
				{
					OnMaxHealthChanged.Broadcast(Data.NewValue);
				});
	//.AddUObject(this,&UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			});
	//.AddUObject(this,&UOverlayWidgetController::ManaChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
	.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});
	//.AddUObject(this,&UOverlayWidgetController::MaxManaChanged);
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
					{
						for (const FGameplayTag& Tag : AssetTags)
						{
							//如果Tag是Message类型Tag
							// For example, say that Tag = Message.HealthPotion
							// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
							FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(TEXT("Message"));// 拿到 "Message" 这个父 Tag 作为参照
							if (Tag.MatchesTag(MessageTag))// 遍历当前 GE 带的所有 Asset Tag，每个 Tag 都问一句：// "你属于 Message 这一族吗？"
							{
								const FWidgetTableRow* Row =  GetTableDataByTag<FWidgetTableRow>(MessageWidgetDataTable,Tag);
								WidgetMessageSignature.Broadcast(*Row);
							}
							
						}
					});
}