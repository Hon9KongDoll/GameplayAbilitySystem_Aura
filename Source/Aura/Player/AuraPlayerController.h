#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Input_Move(const FInputActionValue& InputActionValue);
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> Move_InputAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> AuraInputMappingContext;
};
