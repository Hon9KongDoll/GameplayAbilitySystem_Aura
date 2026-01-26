#include "PlayerController/AuraPlayerController.h"

//Engine
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
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