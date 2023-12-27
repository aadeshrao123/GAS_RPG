// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "RPGGameplayAbility.h"
#include "RPGDamageGamaplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGDamageGamaplayAbility : public URPGGameplayAbility
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
