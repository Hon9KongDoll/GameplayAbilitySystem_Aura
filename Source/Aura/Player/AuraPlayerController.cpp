#include "AuraPlayerController.h"

//Engine
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

	check(AuraInputMappingContext);

	ULocalPlayer* LocalPlayer = GetLocalPlayer();

	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);

	Subsystem->AddMappingContext(AuraInputMappingContext, 0);
	
	bShowMouseCursor = true;

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeGameAndUI);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Move_InputAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Input_Move);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit) return;
	
	PreviousActor = CurrentActor;
	CurrentActor = HitResult.GetActor();
	
	/**
	 * 从光标位置执行射线检测。存在以下几种情况：
	 *
	 * A. PreviousActor 为空 && CurrentActor 为空
	 *     - 不执行任何操作
	 *
	 * B. PreviousActor 为空 && CurrentActor 有效
	 *     - 高亮 CurrentActor
	 *
	 * C. PreviousActor 有效 && CurrentActor 为空
	 *     - 取消高亮 PreviousActor
	 *
	 * D. 两个 Actor 均有效，但 PreviousActor != CurrentActor
	 *     - 取消高亮 PreviousActor，并高亮 CurrentActor
	 *
	 * E. 两个 Actor 均有效，且指向同一个 Actor
	 *     - 不执行任何操作
	 */
	
	if (PreviousActor == nullptr)
	{
		if (CurrentActor != nullptr)
		{
			// Case B
			CurrentActor->HighlightActor();
		}
		else
		{
			// Case A
		}
	}
	else
	{
		if (CurrentActor == nullptr)
		{
			// Case C
			PreviousActor->UnHighlightActor();
		}
		else
		{
			// Case D
			if (PreviousActor != CurrentActor)
			{
				CurrentActor->HighlightActor();
				PreviousActor->UnHighlightActor();
			}
			else
			{
				// Case E
			}
		}
	}
}

void AAuraPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);
		
		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			ControllerPawn->AddMovementInput(MovementDirection, Value.X);
		}
		
		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			ControllerPawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}
