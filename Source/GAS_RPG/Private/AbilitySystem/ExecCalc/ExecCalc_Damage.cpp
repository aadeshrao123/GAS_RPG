// Copyright AadeshRao


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "RPG_GameplayTags.h"
#include "AbilitySystem/Base_AttributeSet.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBase_AttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBase_AttributeSet, BlockChance, Target, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC= ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC= ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	FGameplayEffectSpec EffectSpec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	//Get Damage Set by Caller Magnitude
	float Damage = EffectSpec.GetSetByCallerMagnitude(FRPG_GameplayTags::Get().Damage);

	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	Damage = bBlocked ? Damage / 2.f : Damage;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UBase_AttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
