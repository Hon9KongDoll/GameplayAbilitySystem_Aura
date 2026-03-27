#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"

//Engine
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* TargetDataUnderMouse = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return TargetDataUnderMouse;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();

	// 检查是否受本地控制，并发送数据
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendMouseCurorData();
	}
	else
	{
		// TODO: We are on the server, so listen for target data.
	}
}

void UTargetDataUnderMouse::SendMouseCurorData()
{
	// 作用域内开启预测Key的RAII工具，用来确保客户端预测操作合法同步到服务器
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

	// 在这个作用域内所有操作都带 PredictionKey

	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();

	FHitResult HitResult;

	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();

	TargetData->HitResult = HitResult;

	FGameplayAbilityTargetDataHandle TargetDataHandle;

	TargetDataHandle.Add(TargetData);

	// 用于客户端把目标数据发送到服务器，让服务器执行能力逻辑
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		TargetDataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	// 判断当前 AbilityTask 是否安全且应该触发委托
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		MouseTargetDataDelegate.Broadcast(TargetDataHandle);
	}
}
