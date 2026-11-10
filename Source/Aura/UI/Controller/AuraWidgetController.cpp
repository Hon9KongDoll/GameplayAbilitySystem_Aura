#include "AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParameters(const FWidgetControllerParameters& WidgetControllerParameters)
{
	PlayerController = WidgetControllerParameters.PlayerController;
	PlayerState = WidgetControllerParameters.PlayerState;
	AbilitySystemComponent = WidgetControllerParameters.AbilitySystemComponent;
	AttributeSet = WidgetControllerParameters.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{

}

void UAuraWidgetController::BindCallbacksToDependencies()
{

}
