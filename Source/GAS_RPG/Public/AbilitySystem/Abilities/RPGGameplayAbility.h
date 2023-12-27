// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupTags;

};
