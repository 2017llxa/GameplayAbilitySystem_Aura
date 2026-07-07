// Copyright Druid Mechanics


#include "UI/WidgetController/AuraWidgetController.h"


void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbiltySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitValues()
{
}

void UAuraWidgetController::CallBacksToDepends()
{
}


