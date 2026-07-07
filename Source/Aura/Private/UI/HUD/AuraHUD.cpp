// Copyright Druid Mechanics


#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if ( Overlaywidgetcontroller == nullptr)
	{
		Overlaywidgetcontroller = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		Overlaywidgetcontroller->SetWidgetControllerParams(WCParams);
		Overlaywidgetcontroller->CallBacksToDepends();
		
		return Overlaywidgetcontroller;
	}
	return Overlaywidgetcontroller;
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



