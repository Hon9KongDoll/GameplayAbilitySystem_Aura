#pragma once

#include "CoreMinimal.h"

/**
 * AuraGameplayTags
 *
 * 用于存储原生GameplayTags的单例类
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags Get() { return GameplayTags; }

	void InitializeNativeGameplayTags();

private:
	static FAuraGameplayTags GameplayTags;
};