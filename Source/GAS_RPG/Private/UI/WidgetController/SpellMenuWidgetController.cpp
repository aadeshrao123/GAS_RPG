// Copyright AadeshRao


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "RPG_GameplayTags.h"
#include "SkeletalDebugRendering.h"
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
	GetHeroASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel)
	{
		if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
		{
			SelectedAbility.Status = StatusTag;
			bool bEnableSpendPoints = false;
			bool bEnableEquipSpell = false;
			ShouldEnableButtons(StatusTag, CurrentSpellPoint, bEnableSpendPoints, bEnableEquipSpell);
			FString Description;
			FString NextLevelDescription;
			GetHeroASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);
			SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquipSpell, Description, NextLevelDescription);

		}
		if (AbilityInfo)
		{
			FHeroAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	GetHeroASC()->AbilityEquipped.AddUObject(this, &USpellMenuWidgetController::OnAbilityEquipped);

	GetHeroPS()->OnSpellPointsDelegate.AddLambda
	([this] (const int32 NewValue)
	{
		OnSpellPointsChanged.Broadcast(NewValue);
		CurrentSpellPoint = NewValue;

		bool bEnableSpendPoints = false;
		bool bEnableEquipSpell = false;
		ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoint, bEnableSpendPoints, bEnableEquipSpell);
		FString Description;
		FString NextLevelDescription;
		GetHeroASC()->GetDescriptionsByAbilityTag(SelectedAbility.Ability, Description, NextLevelDescription);
		SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquipSpell, Description, NextLevelDescription);
	}
	);
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	if (bWaitingForEquipSelection)
	{
		const FGameplayTag SelectedAbilityTypeTag = AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType;
		StopWaitForEquipDelegate.Broadcast(SelectedAbilityTypeTag);
		bWaitingForEquipSelection = false;
	}
	
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

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;
	
	bool bEnableSpendPoints = false;
	bool bEnableEquipSpell = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpendPoints, bEnableEquipSpell);
	FString Description;
	FString NextLevelDescription;
	GetHeroASC()->GetDescriptionsByAbilityTag(AbilityTag, Description, NextLevelDescription);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquipSpell, Description, NextLevelDescription);
}

void USpellMenuWidgetController::SpendPointButtonPress()
{
	if (GetHeroASC())
	{
		GetHeroASC()->ServerSpendSpellPoint(SelectedAbility.Ability);
	}
}

void USpellMenuWidgetController::GlobeDeselect()
{
	if (bWaitingForEquipSelection)
	{
		const FGameplayTag SelectedAbilityTypeTag = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
		StopWaitForEquipDelegate.Broadcast(SelectedAbilityTypeTag);
		bWaitingForEquipSelection = false;
	}
	
	SelectedAbility.Ability = FRPG_GameplayTags::Get().Abilities_None;
	SelectedAbility.Status = FRPG_GameplayTags::Get().Abilities_Status_Locked;
	SpellGlobeSelectedDelegate.Broadcast(false, false, FString(), FString());
}

void USpellMenuWidgetController::EquipButtonPressed()
{
	const FGameplayTag AbilityTypeTag = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
	WaitForEquipDelegate.Broadcast(AbilityTypeTag);
	bWaitingForEquipSelection = true;

	const FGameplayTag SelectedStatus = GetHeroASC()->GetStatusFromAbilityTag(SelectedAbility.Ability);
	if (SelectedStatus.MatchesTagExact(FRPG_GameplayTags::Get().Abilities_Status_Equipped))
	{
		SelectedSlot = GetHeroASC()->GetInputFromAbilityTag(SelectedAbility.Ability);
	}
}

void USpellMenuWidgetController::SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType)
{
	if (!bWaitingForEquipSelection) return;

	const FGameplayTag& SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityType;
	if (!SelectedAbilityType.MatchesTagExact(AbilityType)) return;

	GetHeroASC()->ServerEquipAbility(SelectedAbility.Ability, SlotTag);
}

void USpellMenuWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PreviousSlot)
{
	bWaitingForEquipSelection = false;
	const FRPG_GameplayTags RPGTags = FRPG_GameplayTags::Get();
	FHeroAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = RPGTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = RPGTags.Abilities_None;

	//Broadcast empty info if PreviousSlot is a Valid slot. Only if equipping an already-equipped spell
	
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FHeroAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;
	AbilityInfoDelegate.Broadcast(Info);

	StopWaitForEquipDelegate.Broadcast(AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType);
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

