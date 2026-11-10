#include "AuraHUD.h"
#include "Aura/UI/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	check(OverlayWidgetClass);

	OverlayWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
}