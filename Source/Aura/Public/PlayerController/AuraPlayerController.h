#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"


class UInputAction;
class IEnemyInterface;
class USplineComponent;
class UAuraInputConfig;
class UInputMappingContext;

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

	// 自动奔跑
	void AutoRun();

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
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

private:
	// 暂时编译不过
	// TObjectPtr<IEnemyInterface> LastActor;
	// TObjectPtr<IEnemyInterface> ThisActor;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	// 缓存目的地
	FVector CacheDestination;
	// 跟随时间
	float FollowTime;
	// 短按阈值
	float ShortPressThreshold;
	// 目标锁定状态
	uint8 bTargeting : 1;
	// 自动奔跑开关
	uint8 bAutoRunning : 1;
	// 自动奔跑判定范围
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius;
};
