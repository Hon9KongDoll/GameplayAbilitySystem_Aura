#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"

//Engine
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

/* {@ 整体执行流程

	客户端：
	Activate()
		↓
	SendMouseCursorData()
		↓
	FScopedPredictionWindow（开启预测）
		↓
	获取鼠标HitResult
		↓
	ServerSetReplicatedTargetData（发给服务器）
		↓
	本地直接 Broadcast（客户端预测）

	服务器：
	Activate()
		↓
	注册 Delegate 等数据
		↓
	收到 TargetData
		↓
	OnTargetDataReplicatedCallback()
		↓
	Broadcast（服务器执行）

	@}
*/

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

		const FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySpecHandle();

		const FPredictionKey PredictionKey = GetActivationPredictionKey();

		// 当这个 Ability + PredictionKey 的 TargetData 到达时，调用回调函数
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle, PredictionKey).AddUObject(this, &ThisClass::OnTargetDataReplicatedCallback);

		// 尝试立即触发：如果数据已经提前到了，直接执行回调；如果还没到，进入等待
		if (!AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(AbilitySpecHandle, PredictionKey))
		{
			// 等待客户端数据
			SetWaitingOnRemotePlayerData();
		}
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

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ActivationGameplayTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		MouseTargetDataDelegate.Broadcast(TargetDataHandle);
	}
}
