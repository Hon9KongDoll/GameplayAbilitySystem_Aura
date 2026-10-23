#include "AuraGameplayTags.h"

namespace AuraGameplayTags
{
	// 1：Actor/组件已完成初始生成，可以进行扩展。
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_Spawned, "InitState.Spawned", "1: Actor/component has initially spawned and can be extended");
	// 2：所有必需的数据均已加载或完成网络复制，已准备好进行初始化。
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_DataAvailable, "InitState.DataAvailable", "2: All required data has been loaded/replicated and is ready for initialization");
	// 3：该 Actor/组件的现有数据已完成初始化，但尚未准备好进入完整的游戏流程。
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_DataInitialized, "InitState.DataInitialized", "3: The available data has been initialized for this actor/component, but it is not ready for full gameplay");
	// 4：该 Actor/组件已完全就绪，可以参与实际游戏。
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_GameplayReady, "InitState.GameplayReady", "4: The actor/component is fully ready for active gameplay");
}