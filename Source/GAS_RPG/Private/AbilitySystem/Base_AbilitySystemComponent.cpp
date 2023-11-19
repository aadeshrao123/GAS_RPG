// Copyright AadeshRao


#include "AbilitySystem/Base_AbilitySystemComponent.h"

void UBase_AbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBase_AbilitySystemComponent::EffectApplied);
}

void UBase_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                 const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffect)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (FGameplayTag Tag : TagContainer)
	{
		FString TagName = FString::Printf(TEXT("GE Tag Name %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TagName);
	}
}
