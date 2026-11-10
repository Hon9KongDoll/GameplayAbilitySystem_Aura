#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Aura/UI/AuraUserWidget.h"
#include "Aura/UI/Controller/AuraWidgetController.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UAuraWidgetController* GetOverlayWidgetController(const FWidgetControllerParameters& InWidgetControllerParameters);

	UFUNCTION(BlueprintCallable)
	void InitializeOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAuraWidgetController> OverlayWidgetController;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraWidgetController> OverlayWidgetControllerClass;
};
