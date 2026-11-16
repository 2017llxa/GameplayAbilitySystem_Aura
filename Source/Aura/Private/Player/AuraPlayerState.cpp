 // Copyright Druid Mechanics


#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

 AAuraPlayerState::AAuraPlayerState()
 {

 	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
 	
 	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);//复制模式为mix
 	
 	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	
    NetUpdateFrequency = 100.f;
 }

 UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
 {
 	return AbilitySystemComponent;
 }

 void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
 {
	 Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 		
 	DOREPLIFETIME(AAuraPlayerState,Level);
 }

 void AAuraPlayerState::OnRep_Level(int OldLevel)
 {
 	
 }
