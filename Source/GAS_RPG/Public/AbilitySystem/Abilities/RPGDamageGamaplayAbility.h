// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "RPGAbilityTypes.h"
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

	FDamageEffectParams MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DebuffChance = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DebuffFrequency = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DebuffDuration = 5.f;
	
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontages(const TArray<FTaggedMontage>& TaggedMontage) const;
};
