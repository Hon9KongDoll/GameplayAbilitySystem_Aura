#include "Character/AuraCharacter.h"

//Engine
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	// 运动系统调整
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 旋转至运动方向的速率
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400, 0.f);
	// 运动将限制在一个平面
	GetCharacterMovement()->bConstrainToPlane = true;
	// 运动开始时与平面对齐
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// 不使用控制器的旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}