﻿// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCalc_Damage();
	void DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                     FGameplayEffectSpec EffectSpec,
	                     FAggregatorEvaluateParameters EvaluationParameters,
	                     TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsDefs) const;

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
