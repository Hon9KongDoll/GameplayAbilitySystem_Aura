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

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	if (AbilitySystemComponent)
	{
		if (UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::HealthChange);

			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::MaxHealthChange);
		}
	}
}

void UOverlayWidgetController::HealthChange(const FOnAttributeChangeData& Data) const
{
	OnHealthChange.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChange(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChange.Broadcast(Data.NewValue);
}
