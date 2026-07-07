// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSingature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXHealthChangedSingature,float,NewMAXHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSingature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXManaChangedSingature,float,NewMAXMana);

UCLASS(Blueprintable,BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BroadcastInitValues() override;
	virtual void CallBacksToDepends() override;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnHealthChangedSingature OnHealthChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMAXHealthChangedSingature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnManaChangedSingature OnManaChanged;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMAXManaChangedSingature OnMaxManaChanged;
protected:

	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
