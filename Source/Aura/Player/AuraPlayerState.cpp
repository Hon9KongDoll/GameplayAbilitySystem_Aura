#include "AuraPlayerState.h"
#include "Aura/AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AuraAbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AuraAbilitySystemComponent");
	AuraAbilitySystemComponent->SetIsReplicated(true);
	AuraAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AuraAttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AuraAttributeSet");
}
