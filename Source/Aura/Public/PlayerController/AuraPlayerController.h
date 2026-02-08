#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class IEnemyInterface;

struct FInputActionValue;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	// 光标跟踪
	void CursorTrace();

	void Move(const FInputActionValue& InputActionValue);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

private:
	// 暂时编译不过
	// TObjectPtr<IEnemyInterface> LastActor;
	// TObjectPtr<IEnemyInterface> ThisActor;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};
