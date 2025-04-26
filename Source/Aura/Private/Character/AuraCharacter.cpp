#include "Character/AuraCharacter.h"

// Engine
#include "GameFramework/CharacterMovementComponent.h"

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
