// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"


UENUM(BlueprintType)
enum class EEffectApplyPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverLap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
	

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GamePlayEffectClass);
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	bool bDestroyOnEffectRemoved = false;
	
	//及时性游戏效果
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	EEffectApplyPolicy InstantEffectApplyPolicy = EEffectApplyPolicy::DoNotApply;
	
	//持续性游戏效果（未开启周期的话为多少秒之后结束）
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	EEffectApplyPolicy DurationEffectApplyPolicy = EEffectApplyPolicy::DoNotApply;

	//无限游戏效果
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	EEffectApplyPolicy InfiniteEffectApplyPolicy = EEffectApplyPolicy::DoNotApply;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	EEffectRemovePolicy InfiniteEffectRemovePolicy = EEffectRemovePolicy::DoNotRemove;

	//如果当前游戏效果为无限infinite，并且此效果需要移除；那么将其添加到TMap中
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	float ActorLevel;

	
private:


};
