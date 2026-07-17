// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

USTRUCT()
struct FWidgetTableRow :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message = FText();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image = nullptr;
	
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSingature,float,NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXHealthChangedSingature,float,NewMAXHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSingature,float,NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMAXManaChangedSingature,float,NewMAXMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWidgetMessageSignature,FWidgetTableRow,WidgetMessage);



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
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Message")
	FWidgetMessageSignature WidgetMessageSignature;

protected:

	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	//模板函数根据gameplayTag获取表格中的数据行FWidgetTableRow（可作为全局函数，多个地方使用）
	template <typename T>
	T* GetTableDataByTag(UDataTable* DataTable, const FGameplayTag& Tag)
	{
		return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
	}
};
