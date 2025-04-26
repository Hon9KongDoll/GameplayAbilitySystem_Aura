#include "Character/AuraCharacter.h"

// Engine
#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	// ��ɫ�ĳ����Զ�ƥ���ƶ�����
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// ��ת����
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// ���ƽ�ɫ��������ƶ����ض���ƽ����
	GetCharacterMovement()->bConstrainToPlane = true;
	// ����Ϸ��ʼʱ�Զ���������뵽Լ��ƽ��
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// ע ������д��ᵼ�½�ɫ�����޷��ɹ�ƥ�䵽�ƶ�����
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
