// Copyright AadeshRao

#pragma once
#include "GameplayEffectTypes.h"
#include "RPGAbilityTypes.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()
	
	FDamageEffectParams() {};

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffect = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent = nullptr;

	UPROPERTY()
	float BaseDamage = 0.f;

	UPROPERTY()
	float AbilityLevel = 1.f;

	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();
	
	UPROPERTY()
	float DebuffChance = 0.f;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;
};

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
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FRPGGameplayEffectContext* Duplicate() const
	{
		FRPGGameplayEffectContext* NewContext = new FRPGGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	
protected:
	UPROPERTY()
	bool bIsBlockedHit;

	UPROPERTY()
	bool bIsCriticalHit;
};

template<>
struct TStructOpsTypeTraits<FRPGGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FRPGGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};	
};
