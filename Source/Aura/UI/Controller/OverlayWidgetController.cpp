#include "OverlayWidgetController.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	if (UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{
		OnHealthChange.Broadcast(AuraAttributeSet->GetHealth());
		OnMaxHealthChange.Broadcast(AuraAttributeSet->GetMaxHealth());
		
		OnManaChange.Broadcast(AuraAttributeSet->GetMana());
		OnMaxManaChange.Broadcast(AuraAttributeSet->GetMaxMana());
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
			
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				AuraAttributeSet->GetManaAttribute()).AddUObject(this, &ThisClass::ManaChange);
			
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &ThisClass::MaxManaChange);
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

void UOverlayWidgetController::ManaChange(const FOnAttributeChangeData& Data) const
{
	OnManaChange.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChange(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChange.Broadcast(Data.NewValue);
}
