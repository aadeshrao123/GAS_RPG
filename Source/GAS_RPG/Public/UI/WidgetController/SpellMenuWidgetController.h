// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/HeroWidgetController.h"
#include "GameplayTagContainer.h"
#include "RPG_GameplayTags.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled, FString, DescriptionString, FString, NextLevelDescriptionString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature, const FGameplayTag, AbilityType);

/**
 * 
 */

struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};

UCLASS(BlueprintType, Blueprintable)
class GAS_RPG_API USpellMenuWidgetController : public UHeroWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksTODependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FONPlayerStatsChanged OnSpellPointsChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FWaitForEquipSelectionSignature WaitForEquipDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FWaitForEquipSelectionSignature StopWaitForEquipDelegate;

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPress();
	
	UFUNCTION(BlueprintCallable)
	void GlobeDeselect();

	UFUNCTION(BlueprintCallable)
	void EquipButtonPressed();

private:
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoint, bool& bShouldEnableSpendSpellPointsButton, bool& bShouldEnableEquipSpellButton);
	FSelectedAbility SelectedAbility = {FRPG_GameplayTags::Get().Abilities_None, FRPG_GameplayTags::Get().Abilities_Status_Locked};
	int32 CurrentSpellPoint = 0;
	bool bWaitingForEquipSelection = false;
};
