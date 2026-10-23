#include "AuraGameInstance.h"
#include "Aura/AuraGameplayTags.h"

//Engine
#include "Components/GameFrameworkComponentManager.h"

void UAuraGameInstance::Init()
{
	Super::Init();

	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>();
	if (ensure(ComponentManager))
	{
		ComponentManager->RegisterInitState(AuraGameplayTags::InitState_Spawned, false, FGameplayTag());
		ComponentManager->RegisterInitState(AuraGameplayTags::InitState_DataAvailable, false, AuraGameplayTags::InitState_Spawned);
		ComponentManager->RegisterInitState(AuraGameplayTags::InitState_DataInitialized, false, AuraGameplayTags::InitState_DataAvailable);
		ComponentManager->RegisterInitState(AuraGameplayTags::InitState_GameplayReady, false, AuraGameplayTags::InitState_DataInitialized);
	}
}
