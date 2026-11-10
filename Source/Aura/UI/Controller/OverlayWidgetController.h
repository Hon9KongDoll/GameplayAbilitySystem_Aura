#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, float, NewValue);

UCLASS(Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangeSignature OnMaxHealthChange;
};
