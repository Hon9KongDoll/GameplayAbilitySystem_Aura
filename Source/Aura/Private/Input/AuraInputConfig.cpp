#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindInputActionByGameplayTag(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& AuraInputAction : AbilityInputAction)
	{
		if (AuraInputAction.InputAction && AuraInputAction.InputTag == GameplayTag)
		{
			return AuraInputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *GameplayTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
