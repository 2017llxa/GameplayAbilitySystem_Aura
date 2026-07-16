// Copyright Druid Mechanics


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
class IAbilitySystemInterface;

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyGameplayEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GamePlayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle =  TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GamePlayEffectClass,ActorLevel,EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle  = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	//如果当前游戏效果为无限infinite，并且此效果需要移除；那么将其添加到TMap中；
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetASC);
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplyPolicy == EEffectApplyPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverLap)
	{
		ApplyGameplayEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplyPolicy == EEffectApplyPolicy::ApplyOnEndOverLap)
	{
		ApplyGameplayEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	//移除infinite效果
	if (InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetActor)) return;
		
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		
		for (auto& HandlePair: ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key);//移除Effect
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (auto& HandleRemovePair:HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(HandleRemovePair);//移除字典中元素
		}
	}
}

 
