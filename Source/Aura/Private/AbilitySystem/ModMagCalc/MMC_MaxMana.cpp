// Copyright Druid Mechanics


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "Interaction/CombatInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"


UMMC_MaxMana::UMMC_MaxMana()
{
	IntDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(IntDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParamters;
	EvaluationParamters.SourceTags = SourceTags;
	EvaluationParamters.TargetTags = TargetTags;
	
	float Int = 0.f;
	GetCapturedAttributeMagnitude(IntDef,Spec,EvaluationParamters,Int);
	Int = FMath::Max(Int,0);
	
	ICombatInterface * CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel =  CombatInterface->GetPlayerLevel();
	
	return 50.f + 2.5f * Int + 15.f * PlayerLevel;
}


