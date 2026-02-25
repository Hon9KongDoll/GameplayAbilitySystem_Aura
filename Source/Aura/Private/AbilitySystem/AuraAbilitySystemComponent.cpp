#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/GameplayAbility/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbility(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& GameplayAbility : GameplayAbilities)
	{
		FGameplayAbilitySpec GameplayAbilitySpec = FGameplayAbilitySpec(GameplayAbility, 1);

		if (UAuraGameplayAbility* AuraGameplayAbility = Cast<UAuraGameplayAbility>(GameplayAbilitySpec.Ability))
		{
			GameplayAbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraGameplayAbility->StartupInputTag);

			GiveAbility(GameplayAbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);

			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InAbilitySystemComponent, const FGameplayEffectSpec& InEffectSpec, FActiveGameplayEffectHandle InActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	InEffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
