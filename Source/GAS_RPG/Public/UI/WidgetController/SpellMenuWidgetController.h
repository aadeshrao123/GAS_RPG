// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/HeroWidgetController.h"
#include "GameplayTagContainer.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled);

/**
 * 
 */
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

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

private:
	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoint, bool& bShouldEnableSpendSpellPointsButton, bool& bShouldEnableEquipSpellButton);
};
