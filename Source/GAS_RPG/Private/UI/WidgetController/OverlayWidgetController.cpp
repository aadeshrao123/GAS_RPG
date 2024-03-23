// Copyright AadeshRao


#include "UI/WidgetController/OverlayWidgetController.h"

#include "RPG_GameplayTags.h"
#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "AbilitySystem/Base_AttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/Hero_PlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetHeroAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetHeroAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetHeroAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetHeroAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksTODependencies()
{
	GetHeroPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	GetHeroPS()->OnLevelChangedDelegate.AddLambda
	(
		[this](int32 NewValue)
		{
			OnPlayerLevelChangedDelegate.Broadcast(NewValue);
		}
	);

	const UBase_AttributeSet* BaseAttributeSet = CastChecked<UBase_AttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
		);

	if (GetHeroASC())
	{
		GetHeroASC()->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
		if (GetHeroASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			GetHeroASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}
		
		GetHeroASC()->EffectAssetTags.AddLambda(
[this](const FGameplayTagContainer& AssetTag)
		{
			for (FGameplayTag Tag : AssetTag)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					FUIWidgetRow* Row = GetDataTableByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowSignature.Broadcast(*Row);
				}
			}
		}
		);
	}
}

void UOverlayWidgetController::OnXPChanged(int32 NewXp)
{
	const ULevelUpInfo* LevelUpInfo = GetHeroPS()->LevelUpInfo;

	checkf(LevelUpInfo, TEXT("You haven't filled the levelupinfo in Player state. Go and fill it"));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXp);
	const int32 MaxLevel = LevelUpInfo->LevelUpInfo.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 CurrentLevelXPRequirements = LevelUpInfo->LevelUpInfo[Level].LevelUPRequirement;
		const int32 PreviousLevelXPRequirements = LevelUpInfo->LevelUpInfo[Level - 1].LevelUPRequirement;

		const int32 DeltaLevelRequirements = CurrentLevelXPRequirements - PreviousLevelXPRequirements;
		const int32 XPForThisLevel =  NewXp - PreviousLevelXPRequirements;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirements);
		OnXPPercentageChangedDelegate.Broadcast(XPBarPercent);

	}
	
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const
{
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
}
