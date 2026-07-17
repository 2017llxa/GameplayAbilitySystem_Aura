// Copyright Druid Mechanics


#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if ( OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->CallBacksToDepends();
		
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(AuraUserWidgetClass,TEXT("AuraUserWidgetClass is not set"));
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass is not set"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),AuraUserWidgetClass);
	AuraUserWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParams WCParams = FWidgetControllerParams(PC,PS,ASC,AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);
	
	AuraUserWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitValues();
	Widget->AddToViewport();
}



