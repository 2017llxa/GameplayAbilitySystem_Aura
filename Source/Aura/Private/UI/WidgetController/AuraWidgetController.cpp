// Copyright Druid Mechanics


#include "UI/WidgetController/AuraWidgetController.h"


void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbiltySystemComponent = WCParams.AbiltySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}
