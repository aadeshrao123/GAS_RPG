// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "RPGProjectileSpell.h"
#include "RPGFirebolt.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGFirebolt : public URPGProjectileSpell
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

};
