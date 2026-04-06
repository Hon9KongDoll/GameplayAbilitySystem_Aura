#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxHealth();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const;

private:
	// 捕获目标的活力属性
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
