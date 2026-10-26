#include "AuraPawnExtensionComponent.h"
#include "Aura/AuraGameplayTags.h"

//Engine
#include "Components/GameFrameworkComponentDelegates.h"

const FName UAuraPawnExtensionComponent::NAME_ActorFeatureName("PawnExtension");

void UAuraPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();

	// 监听 Pawn 扩展组件的初始化状态变化。
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);

	// 通知系统生成阶段已完成，然后继续尝试执行后续初始化流程。
	ensure(TryToChangeInitState(AuraGameplayTags::InitState_Spawned));
	CheckDefaultInitialization();
}

bool UAuraPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();

	if (!CurrentState.IsValid() && DesiredState == AuraGameplayTags::InitState_Spawned)
	{
		// 只要我们处于有效的 Pawn 上，就视为已完成生成。
		if (Pawn)
		{
			return true;
		}
	}
	else if (CurrentState == AuraGameplayTags::InitState_Spawned && DesiredState == AuraGameplayTags::InitState_DataAvailable)
	{

	}

	return false;
}

void UAuraPawnExtensionComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
}

void UAuraPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	// 如果另一个功能现在已进入 DataAvailable 状态，则检查是否应转换到 DataInitialized 状态。
	if (Params.FeatureName != NAME_ActorFeatureName)
	{
		if (Params.FeatureState == AuraGameplayTags::InitState_DataAvailable)
		{
			CheckDefaultInitialization();
		}
	}
}

void UAuraPawnExtensionComponent::CheckDefaultInitialization()
{
	// 在检查当前初始化进度之前，先尝试推进我们可能依赖的其他功能的初始化流程。
	CheckDefaultInitializationForImplementers();

	static const TArray<FGameplayTag> StateChain = {
	AuraGameplayTags::InitState_Spawned,
	AuraGameplayTags::InitState_DataAvailable,
	AuraGameplayTags::InitState_DataInitialized,
	AuraGameplayTags::InitState_GameplayReady };

	// 此操作会尝试从 Spawned 状态（仅在 BeginPlay 中设置）开始，
	// 依次推进各个数据初始化阶段，直到达到 Gameplay Ready（游戏就绪）状态。
	ContinueInitStateChain(StateChain);
}

void UAuraPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	const APawn* Pawn = GetPawn<APawn>();
	ensureAlwaysMsgf((Pawn != nullptr), TEXT("AuraPawnExtensionComponent on[% s] can only be added to Pawn actors."), *GetNameSafe(GetOwner()));

	TArray<UActorComponent*> PawnExtensionComponents;
	Pawn->GetComponents(UAuraPawnExtensionComponent::StaticClass(), PawnExtensionComponents);
	ensureAlwaysMsgf((PawnExtensionComponents.Num() == 1), TEXT("Only one AuraPawnExtensionComponent should exist on [%s]."), *GetNameSafe(GetOwner()));

	// 尽早向初始化状态系统注册；
	// 只有当前世界是游戏世界时，此操作才会生效。
	RegisterInitStateFeature();
}