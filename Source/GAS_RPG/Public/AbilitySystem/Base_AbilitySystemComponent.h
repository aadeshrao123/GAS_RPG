// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Base_AbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, UBase_AbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&)

/**
 * 
 */

UCLASS()
class GAS_RPG_API UBase_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	bool bStartupAbilitiesGiven = false;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbility);
	void AbilityInputTagHeld(FGameplayTag& InputTag);
	void AbilityInputTagReleased(FGameplayTag& InputTag);
	void ForEachAbility(const FForEachAbility& Delegate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
protected:

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffect);

	virtual void OnRep_ActivateAbilities() override;
	
};
