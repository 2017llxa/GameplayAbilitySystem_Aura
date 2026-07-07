 // Copyright Druid Mechanics


#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

 AAuraPlayerState::AAuraPlayerState()
 {

 	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
 	
 	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);//复制模式为mix
 	
 	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
    NetUpdateFrequency = 100.f;
 }

 UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
 {
 	return AbilitySystemComponent;
 }
