#include "HUD/AuraHUD.h"
#include "UserWidget/WidgetController/OverlayWidgetController.cpp"

//Engine
#include "UserWidget/Widget/AuraUserWidget.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(OverlapWidgetClass);

	check(OverlayWidgetControllerClass);

	if (OverlapWidget) return;

	OverlapWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlapWidgetClass);

	FWidgetControllerParams WCParams(PC, PS, ASC, AS);

	OverlapWidget->SetWidgetController(GetOverlayWidgetController(WCParams));

	OverlapWidget->AddToViewport();
}