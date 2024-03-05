// Copyright AadeshRao


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/Hero_PlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	OnSpellPointsChanged.Broadcast(GetHeroPS()->GetSpellPoints());	
}

void USpellMenuWidgetController::BindCallbacksTODependencies()
{
	GetHeroASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
	{
		if (AbilityInfo)
		{
			FHeroAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	}
	);
	GetHeroPS()->OnSpellPointsDelegate.AddLambda
	([this] (const int32 NewValue)
	{
		OnSpellPointsChanged.Broadcast(NewValue);
	}
	);
}
