#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();

	// 添加角色能力
	void AddCharacterAbility(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities);

	// 标签按键输入 - 持续
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	// 标签按键输入 - 松开
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

protected:
	void EffectApplied(UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayEffectSpec& InEffectSpec, FActiveGameplayEffectHandle InActiveEffectHandle);

public:
	FEffectAssetTags EffectAssetTags;
};
