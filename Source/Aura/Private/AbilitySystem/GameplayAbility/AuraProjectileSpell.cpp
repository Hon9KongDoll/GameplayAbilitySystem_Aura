#include "AbilitySystem/GameplayAbility/AuraProjectileSpell.h"
#include "Interface/CombatInterface.h"
#include "Actor/ProjectileActor.h"


//Engine
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	SpawnProjectile();
}

void UAuraProjectileSpell::SpawnProjectile()
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	// 用于生成前可修改 Actor
	// 且要调用 FinishSpawningActor

	FVector SpawnLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo());

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);

	if (ProjectileClass == nullptr) return;

	AProjectileActor* ProjectileActor = GetWorld()->SpawnActorDeferred<AProjectileActor>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	ProjectileActor->FinishSpawning(SpawnTransform);
}
