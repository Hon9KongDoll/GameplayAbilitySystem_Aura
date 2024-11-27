// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	// 角色向加速方向旋转
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 每秒旋转的变化
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// 运动将被限制在一个平面上
	GetCharacterMovement()->bConstrainToPlane = true;
	// 如果为true并且平面约束被启用，那么更新后的组件将在第一次附加到平面上
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
