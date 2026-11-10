#include "AuraCharacter.h"
#include "Aura/Player/AuraPlayerState.h"
#include "Aura/UI/HUD/AuraHUD.h"

// Engine
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter(const FObjectInitializer& ObjectInitializer)
{
	// 是否根据角色的移动方向自动旋转自身朝向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 根据目标旋转方向进行旋转时的最大旋转速度
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// 限制角色只能在一个指定的平面内移动，不能离开这个平面
	GetCharacterMovement()->bConstrainToPlane = true;
	// 当角色开始移动时，自动将角色对齐到指定的约束平面上。
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server
	InitializeAbilitySystemComponent();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client
	InitializeAbilitySystemComponent();
}

void AAuraCharacter::InitializeAbilitySystemComponent()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();

	check(AuraPlayerState);

	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AuraAbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AuraAttributeSet = AuraPlayerState->GetAttributeSet();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AuraHUD->InitializeOverlayWidget(PC, AuraPlayerState, AuraAbilitySystemComponent, AuraAttributeSet);
		}
	}
}
