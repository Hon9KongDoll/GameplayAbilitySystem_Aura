#include "Character/AuraCharacter.h"
#include "PlayerState/AuraPlayerState.h"

// Engine
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

AAuraCharacter::AAuraCharacter()
{
	// 角色的朝向自动匹配移动方向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// 限制角色或物体的移动在特定的平面上
	GetCharacterMovement()->bConstrainToPlane = true;
	// 在游戏开始时自动将对象对齐到约束平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// 注 ：这里写错会导致角色朝向无法成功匹配到移动方向
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for the Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
