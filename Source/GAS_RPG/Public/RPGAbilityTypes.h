// Copyright AadeshRao

#pragma once
#include "GameplayEffectTypes.h"
#include "RPGAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FRPGGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
public:

	bool IsBlockedHit() const {return bIsBlockedHit; }
	bool IsCriticalHit() const {return bIsCriticalHit; }

	void SetIsBlockedHit(bool bIsInBlockedHit) {bIsBlockedHit = bIsInBlockedHit; }
	void SetIsCriticalHit(bool bIsInCriticalHit) {bIsCriticalHit = bIsInCriticalHit; }
	
	
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContextHandle::StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	
protected:
	UPROPERTY()
	bool bIsBlockedHit;

	UPROPERTY()
	bool bIsCriticalHit;

	
};
