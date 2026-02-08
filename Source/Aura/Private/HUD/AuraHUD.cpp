#include "HUD/AuraHUD.h"

//Engine
#include "UserWidget/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlapWidgetClass);
	Widget->AddToViewport();
}
