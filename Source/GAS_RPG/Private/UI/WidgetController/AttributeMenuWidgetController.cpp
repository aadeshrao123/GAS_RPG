// Copyright AadeshRao


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AssetTypeCategories.h"
#include "RPG_GameplayTags.h"
#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "AbilitySystem/Base_AttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/Hero_PlayerState.h"

void UAttributeMenuWidgetController::BindCallbacksTODependencies()
{
	check(AttributeInfo);
	for (auto Pair : GetHeroAS()->TagsToAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastInitialInfo(Pair.Key, Pair.Value());
		}
		);
	}

	GetHeroPS()->OnAttributePointsChangedDelegate.AddLambda
	([this] (const int32 NewValue)
	{
		OnAttributePointsChanged.Broadcast(NewValue);
	}
	);
	GetHeroPS()->OnSpellPointsDelegate.AddLambda
	([this] (const int32 NewValue)
	{
		OnSpellPointsChanged.Broadcast(NewValue);
	}
	);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);
	for (auto Pair : GetHeroAS()->TagsToAttribute)
	{
		BroadcastInitialInfo(Pair.Key, Pair.Value());
	}

	OnAttributePointsChanged.Broadcast(GetHeroPS()->GetAttributePoints());	
	OnSpellPointsChanged.Broadcast(GetHeroPS()->GetSpellPoints());	
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UBase_AbilitySystemComponent* HeroASC = CastChecked<UBase_AbilitySystemComponent>(AbilitySystemComponent);
	HeroASC->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastInitialInfo(const FGameplayTag& AttributeTag,
                                                          const FGameplayAttribute& Attribute) const
{
	FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);

}
