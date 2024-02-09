// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "HeroWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FRPGAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSignatureAttributeInfoDelegate, const FRPGAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAS_RPG_API UAttributeMenuWidgetController : public UHeroWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksTODependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FSignatureAttributeInfoDelegate AttributeInfoDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FONPlayerStatsChanged OnAttributePointsChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FONPlayerStatsChanged OnSpellPointsChanged;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastInitialInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
