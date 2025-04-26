#include "PlayerController/AuraPlayerController.h"
#include "Interface/EnemyInterface.h"

// Engine
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeGameAndUI);
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

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	if (!HitResult.bBlockingHit) return;

	LastEnemyActor = ThisEnemyActor;
	ThisEnemyActor = Cast<IEnemyInterface>(HitResult.GetActor());

	if (LastEnemyActor == nullptr)
	{
		if (ThisEnemyActor == nullptr) {}
		else
		{
			ThisEnemyActor->HighLightActor();
		}
	}
	else
	{
		if (ThisEnemyActor == nullptr)
		{
			LastEnemyActor->UnHighLightActor();
		}
		else
		{
			if (LastEnemyActor == ThisEnemyActor) {}
			else
			{
				LastEnemyActor->UnHighLightActor();
				ThisEnemyActor->HighLightActor();
			}
		}
	}
}
