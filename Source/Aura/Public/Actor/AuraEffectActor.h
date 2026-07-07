// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

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

	//及时性游戏效果
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	//持续性游戏效果（多少秒之后结束）
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "ApplyEffect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

private:


};
