#include "Character/AuraCharacter.h"
#include "PlayerState/AuraPlayerState.h"

// Engine
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

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
