#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	// 指定要捕获智力属性
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	// 要捕获的属性来源
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	// true：在效果创建时锁定数值
	// false：每次计算都用最新值
	IntelligenceDef.bSnapshot = false;

	// 作用：告诉系统要抓哪些属性
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// 从源和目标中收集标签
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// 让属性计算考虑标签影响
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParameters, Intelligence);

	UObject* SourceObject = Spec.GetContext().GetSourceObject();
	const int32 PlayerLevel = ICombatInterface::Execute_GetCharacterLevel(SourceObject);

	return 50.f + 2.5f * Intelligence + 15.f * PlayerLevel;
}

