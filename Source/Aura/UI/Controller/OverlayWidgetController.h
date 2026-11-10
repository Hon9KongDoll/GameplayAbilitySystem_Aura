#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "GameplayEffectTypes.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, const float&, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, const float&, NewValue);

UCLASS(Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

private:
	void HealthChange(const FOnAttributeChangeData& Data) const;
	void MaxHealthChange(const FOnAttributeChangeData& Data) const;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangeSignature OnMaxHealthChange;
};
