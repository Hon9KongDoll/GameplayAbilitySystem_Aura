#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class IEnemyInterface;
class UAuraInputConfig;

struct FInputActionValue;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	// 光标跟踪
	void CursorTrace();

	void Move(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	// 输入操作关联游戏标签 - 资产表
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> AuraInputConfig;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

private:
	// 暂时编译不过
	// TObjectPtr<IEnemyInterface> LastActor;
	// TObjectPtr<IEnemyInterface> ThisActor;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};
