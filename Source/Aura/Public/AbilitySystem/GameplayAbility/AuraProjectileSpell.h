#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class AProjectileActor;

UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void SpawnProjectile();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectileActor> ProjectileClass;
};
