#include "AuraHUD.h"

UAuraWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParameters& InWidgetControllerParameters)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UAuraWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParameters(InWidgetControllerParameters);
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitializeOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(OverlayWidgetClass);
	check(OverlayWidgetControllerClass);

	FWidgetControllerParameters WidgetControllerParameters(PC, PS, ASC, AS);
	UAuraWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParameters);

	if (OverlayWidget == nullptr)
	{
		OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
		OverlayWidget->SetWidgetController(WidgetController);
		WidgetController->BroadcastInitialValues();
		OverlayWidget->AddToViewport();
	}
}
