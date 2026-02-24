#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbility(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& GameplayAbility : GameplayAbilities)
	{
		FGameplayAbilitySpec GameplayAbilitySpec = FGameplayAbilitySpec(GameplayAbility, 1);

		// GiveAbility(GameplayAbilitySpec);

		GiveAbilityAndActivateOnce(GameplayAbilitySpec);
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayEffectSpec& InEffectSpec, FActiveGameplayEffectHandle InActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	InEffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
