#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

// Engine
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

AAuraEnemy::AAuraEnemy()
{
	// 设置碰撞通道的响应方式
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	LeftWeapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	RightWeapon->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));
}

void AAuraEnemy::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_VALUE);

	LeftWeapon->SetRenderCustomDepth(true);
	LeftWeapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_VALUE);

	RightWeapon->SetRenderCustomDepth(true);
	RightWeapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_VALUE);
}

void AAuraEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);

	LeftWeapon->SetRenderCustomDepth(false);

	RightWeapon->SetRenderCustomDepth(false);
}
