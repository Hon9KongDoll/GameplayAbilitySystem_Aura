#include "PlayerController/AuraPlayerController.h"

// Engine
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// GetLocalPlayer() : ���ظÿ������� ULocalPlayer���������򷵻� Null
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(AuraInputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// ��ȡ�ƶ���������
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	// ��ȡ��������ת��ֻ��Ҫ Yaw �� ��ˮƽ��ת
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//  ���㳯ǰ�ͳ��ҵ����緽��
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn())
	{
		ControllerPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControllerPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}
