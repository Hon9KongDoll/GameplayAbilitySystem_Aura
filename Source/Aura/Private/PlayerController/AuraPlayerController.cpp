#include "PlayerController/AuraPlayerController.h"
#include "Interface/EnemyInterface.h"

//Engine
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

	// 断言 - 如果为false直接崩溃
	check(AuraContext)

	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(AuraContext, 0);
	}

	// 显示鼠标光标
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// 设置输入模式内容
	FInputModeGameAndUI InputMoceGameAndUI;
	InputMoceGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 设置鼠标锁定到窗口模式
	InputMoceGameAndUI.SetHideCursorDuringCapture(false); // 当窗口捕捉到光标不隐藏
	SetInputMode(InputMoceGameAndUI);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 使用的增强输入将输入组件获取
	// 该转换如果失败触发断言
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	// 绑定输入动作到函数
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorResult);
	if (!CursorResult.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorResult.GetActor());

	/**
	 * 从鼠标光标位置进行射线检测（Line Trace），可能出现以下几种情况：
	 *
	 * A. LastActor 为空，且 ThisActor 为空
	 *    - 不做任何处理
	 *
	 * B. LastActor 为空，且 ThisActor 有效
	 *    - 高亮显示 ThisActor
	 *
	 * C. LastActor 有效，且 ThisActor 为空
	 *    - 取消高亮显示 LastActor
	 *
	 * D. 两个 Actor 都有效，但 LastActor != ThisActor
	 *    - 取消高亮显示 LastActor，并高亮显示 ThisActor
	 *
	 * E. 两个 Actor 都有效，且是同一个 Actor
	 *    - 不做任何处理
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr)
		{
			// A.不做任何处理
		}
		else
		{
			// B.高亮显示ThisActor
			ThisActor->HighLightAcrot();
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			// C.取消高亮显示LastActor
			LastActor->UnHighLightAcrot();
		}
		else
		{
			if (ThisActor == LastActor)
			{
				// E.不做任何处理
			}
			else
			{
				// D.取消高亮显示LastActor，并高亮显示ThisActor
				LastActor->UnHighLightAcrot();
				ThisActor->HighLightAcrot();
			}
		}
	}
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotator = GetControlRotation();

	// 控制器的旋转跟随玩家的视角,因此需要设置旋转和朝向
	// 根据控制器Yaw创建新的旋转
	const FRotator YawRotation{ 0, Rotator.Yaw, 0 };

	// FRotationMatrix类是旋转构造的旋转矩阵,通过矩阵可以将旋转应用于向量,以便在3D空间中将其旋转
	// GetUnitAxis用于获取旋转矩阵对应轴的向量
	const FVector ForwardDirction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//在控制的pawn上应用输入移动
	if (auto ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirction, InputAxisVector.Y);
		//输入中X是水平轴AD
		ControlledPawn->AddMovementInput(RightDirction, InputAxisVector.X);
	}
}
