#include "Character/AuraCharacterBase.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

//Engine
#include "Components/SkeletalMeshComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

FVector AAuraCharacterBase::GetCombatSocketLocation_Implementation()
{
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(AbilitySystemComponent);

	check(GameplayEffectClass);

	const FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();

	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), AbilitySystemComponent);
}

void AAuraCharacterBase::InitializeDefaultAttributes()
{
	ApplyGameplayEffectToSelf(DefaultPrimaryAttributesGE, 1.f);

	ApplyGameplayEffectToSelf(DefaultSecondaryAttributesGE, 1.f);
}

void AAuraCharacterBase::AddCharacterStartupAbility()
{
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);

	// 服务器添加角色能力，同步到客户端
	if (!HasAuthority()) return;

	AuraAbilitySystemComponent->AddCharacterAbility(StartupAbilities);
}
