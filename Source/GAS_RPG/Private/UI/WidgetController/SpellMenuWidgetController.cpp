// Copyright AadeshRao


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "RPG_GameplayTags.h"
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

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	const FRPG_GameplayTags RPGTags = FRPG_GameplayTags::Get();
	const int32 SpellPoints = GetHeroPS()->GetSpellPoints();
	FGameplayTag AbilityStatus;

	const bool bIsTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(RPGTags.Abilities_None);
	FGameplayAbilitySpec* AbilitySpec = GetHeroASC()->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecValid = AbilitySpec != nullptr;

	if (!bIsTagValid || bTagNone || !bSpecValid)
	{
		AbilityStatus = RPGTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetHeroASC()->GetStatusFromSpec(*AbilitySpec);
	}

	bool bEnableSpendPoints = false;
	bool bEnableEquipSpell = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpendPoints, bEnableEquipSpell);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquipSpell);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoint,
	bool& bShouldEnableSpendSpellPointsButton, bool& bShouldEnableEquipSpellButton)
{
	const FRPG_GameplayTags RPGTags = FRPG_GameplayTags::Get();
	bShouldEnableSpendSpellPointsButton = false;
	bShouldEnableEquipSpellButton =false;
	
	if (AbilityStatus.MatchesTagExact(RPGTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipSpellButton = true;
		if (SpellPoint > 0)
		{
			bShouldEnableSpendSpellPointsButton = true;
		}
	}
	else if(AbilityStatus.MatchesTagExact(RPGTags.Abilities_Status_Eligible))
	{
		if (SpellPoint > 0)
		{
			bShouldEnableSpendSpellPointsButton = true;
		}
	}
	else if(AbilityStatus.MatchesTagExact(RPGTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipSpellButton = true;
		if (SpellPoint > 0)
		{
			bShouldEnableSpendSpellPointsButton = true;
		}
	}
}

