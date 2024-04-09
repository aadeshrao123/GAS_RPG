﻿// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "RPGGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "RPGDamageGamaplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGDamageGamaplayAbility : public URPGGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;
	
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontages(const TArray<FTaggedMontage>& TaggedMontage) const;
};
