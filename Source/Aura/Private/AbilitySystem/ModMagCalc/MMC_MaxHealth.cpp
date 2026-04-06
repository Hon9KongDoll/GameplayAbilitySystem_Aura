#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// 指定要捕获活力属性
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	// 要捕获的属性来源
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	// true：在效果创建时锁定数值
	// false：每次计算都用最新值
	VigorDef.bSnapshot = false;

	// 作用：告诉系统要抓哪些属性
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// 从源和目标中收集标签
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// 让属性计算考虑标签影响
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);

	UObject* SourceObject = Spec.GetContext().GetSourceObject();
	const int32 PlayerLevel = ICombatInterface::Execute_GetCharacterLevel(SourceObject);

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}