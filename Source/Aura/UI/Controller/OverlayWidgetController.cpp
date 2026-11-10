#include "OverlayWidgetController.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	if (UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{
		OnHealthChange.Broadcast(AuraAttributeSet->GetHealth());
		OnMaxHealthChange.Broadcast(AuraAttributeSet->GetMaxHealth());
	}
}
