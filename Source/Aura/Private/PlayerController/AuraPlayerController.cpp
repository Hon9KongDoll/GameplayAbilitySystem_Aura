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

	// GetLocalPlayer() : 返回该控制器的 ULocalPlayer，不存在则返回 Null
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(AuraInputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// 获取移动输入向量
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	// 获取控制器旋转，只需要 Yaw 角 ：水平旋转
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//  计算朝前和朝右的世界方向
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
