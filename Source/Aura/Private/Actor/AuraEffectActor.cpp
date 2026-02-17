#include "Actor/AuraEffectActor.h"

//Engine
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* InTargetActor, TSubclassOf<UGameplayEffect> InGameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor);
	
	if (TargetASC == nullptr) return;

	check(InGameplayEffectClass);

	FGameplayEffectContextHandle EffectContextHandle =  TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(InGameplayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// 判断 GameplayEffect 是否为无限效果类型
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	// 如果为无限效果类型,且结束重叠后需要移除，则保存起来用于后续操作
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandleMap.Add(ActiveEffectHandle, TargetASC);
	}
}

void AAuraEffectActor::OnBeginOverlap(AActor* InTargetActor)
{
	// 开始重叠 - 应用即时游戏效果
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(InTargetActor, InstantGameplayEffectClass);
	}

	// 开始重叠 - 应用持续游戏效果
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(InTargetActor, DurationGameplayEffectClass);
	}

	// 开始重叠 - 应用无限游戏效果
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(InTargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* InTargetActor)
{
	// 结束重叠 - 应用即时游戏效果
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(InTargetActor, InstantGameplayEffectClass);
	}

	// 结束重叠 - 应用持续游戏效果
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(InTargetActor, DurationGameplayEffectClass);
	}

	// 结束重叠 - 应用无限游戏效果
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(InTargetActor, InfiniteGameplayEffectClass);
	}

	// 结束重叠 - 移除施加的无限游戏效果
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor);

		if (TargetASC == nullptr) return;

		TArray<FActiveGameplayEffectHandle> ActiveEffectHandleToRemoveArray;

		for (const TPair<FActiveGameplayEffectHandle, UAbilitySystemComponent*>& HandlePair : ActiveEffectHandleMap)
		{
			// 判断激活的效果句柄关联的的ASC是否为TargetActor-ASC
			if (HandlePair.Value == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);

				// 将移除的激活效果句柄保存起来，从ActiveEffectHandleMap中删除
				ActiveEffectHandleToRemoveArray.Add(HandlePair.Key);
			}
		}

		for (const FActiveGameplayEffectHandle& HandleValue : ActiveEffectHandleToRemoveArray)
		{
			ActiveEffectHandleMap.FindAndRemoveChecked(HandleValue);
		}
	}
}
