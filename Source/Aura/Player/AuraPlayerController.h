#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Aura/Interface/EnemyInterface.h"
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

	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void CursorTrace();
	
	void Input_Move(const FInputActionValue& InputActionValue);
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> Move_InputAction;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> AuraInputMappingContext;
	
private:
	TScriptInterface<IEnemyInterface> PreviousActor;
	TScriptInterface<IEnemyInterface> CurrentActor;
};
