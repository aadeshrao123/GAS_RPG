// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/HeroWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

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
};
