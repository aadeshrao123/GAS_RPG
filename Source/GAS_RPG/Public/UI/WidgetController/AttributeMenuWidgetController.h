// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "HeroWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UAttributeMenuWidgetController : public UHeroWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksTODependencies() override;
	virtual void BroadcastInitialValues() override;
};
