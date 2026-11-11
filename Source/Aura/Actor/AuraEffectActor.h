#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

// 效果应用策略
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	// 在开始重叠时应用
	ApplyOnBeginOverlap,
	// 在结束重叠时应用
	ApplyOnEndOverlap,
	// 不应用
	DoNotApply
};

// 效果移除策略
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	// 在结束重叠时移除
	RemoveOnEndOverlap,
	// 不移除
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffect(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffect);

	UFUNCTION(BlueprintCallable)
	void BeginOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void EndOverlap(AActor* TargetActor);
	
protected:
	// 效果移除时是否销毁
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 bDestroyOnEffectRemoval : 1 {false};

	// 即时游戏效果类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	// 即时效果应用策略
	UPROPERTY(EditDefaultsOnly)
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// 持续时间游戏效果类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	// 持续时间效果应用策略
	UPROPERTY(EditDefaultsOnly)
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// 无限游戏效果类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	// 无限效果应用策略
	UPROPERTY(EditDefaultsOnly)
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	// 无限效果移除策略
	UPROPERTY(EditDefaultsOnly)
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::DoNotRemove;
};
