// Copyright AadeshRao


#include "AbilitySystem/Base_AbilitySystemComponent.h"

#include "RPG_GameplayTags.h"

void UBase_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBase_AbilitySystemComponent::EffectApplied);

	const FRPG_GameplayTags& GameplayTags = FRPG_GameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Tag : %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UBase_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                 const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffect)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
