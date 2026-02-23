#include "HUD/AuraHUD.h"
#include "UserWidget/Widget/AuraUserWidget.h"
#include "UserWidget/WidgetController/OverlayWidgetController.h"
#include "UserWidget/WidgetController/AttributeMenuWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}

	return AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(OverlapWidgetClass);

	check(OverlayWidgetControllerClass);

	if (OverlapWidget) return;

	OverlapWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlapWidgetClass);

	const FWidgetControllerParams WCParams(PC, PS, ASC, AS);

	OverlapWidget->SetWidgetController(GetOverlayWidgetController(WCParams));

	OverlayWidgetController->BroadcastInitialValues();

	OverlapWidget->AddToViewport();
}