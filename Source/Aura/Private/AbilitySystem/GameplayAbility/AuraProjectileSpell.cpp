#include "AbilitySystem/GameplayAbility/AuraProjectileSpell.h"
#include "Interface/CombatInterface.h"
#include "Actor/ProjectileActor.h"

//Engine
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	FVector SpawnLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo());

	FRotator Rotator = (ProjectileTargetLocation - SpawnLocation).Rotation();
	Rotator.Pitch = 0.f;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(Rotator.Quaternion());

	if (ProjectileClass == nullptr) return;

	// SpawnActorDeferred
	// 创建一个未完成的 Actor，先进行配置，再手动完成生成(FinishSpawning)
	AProjectileActor* ProjectileActor = GetWorld()->SpawnActorDeferred<AProjectileActor>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//TODO: 为该投射物分配一个用于造成伤害的游戏效果规格
	UAbilitySystemComponent* SorceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle SpecHandle = SorceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SorceASC->MakeEffectContext());

	ProjectileActor->DamageEffectSpecHandle = SpecHandle;

	ProjectileActor->FinishSpawning(SpawnTransform);
}
