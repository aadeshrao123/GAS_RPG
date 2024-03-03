// Copyright AadeshRao


#include "UI/WidgetController/HeroWidgetController.h"

#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "AbilitySystem/Base_AttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/Hero_PlayerController.h"
#include "Player/Hero_PlayerState.h"

void UHeroWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UHeroWidgetController::BroadcastInitialValues()
{
	
}

void UHeroWidgetController::BindCallbacksTODependencies()
{
	
}

void UHeroWidgetController::BroadcastAbilityInfo()
{
	if (!GetHeroASC()->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FHeroAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(HeroAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = GetHeroASC()->GetInputTagFromSpec(AbilitySpec);
		Info.StatusTag = GetHeroASC()->GetStatusFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	GetHeroASC()->ForEachAbility(BroadcastDelegate);
}

AHero_PlayerController* UHeroWidgetController::GetHeroPC()
{
	if (HeroPlayerController == nullptr)
	{
		HeroPlayerController = Cast<AHero_PlayerController>(PlayerController);
	}
	return HeroPlayerController;
}

AHero_PlayerState* UHeroWidgetController::GetHeroPS()
{
	if (HeroPlayerState == nullptr)
	{
		HeroPlayerState = Cast<AHero_PlayerState>(PlayerState);
	}
	return HeroPlayerState;
}

UBase_AbilitySystemComponent* UHeroWidgetController::GetHeroASC()
{
	if (HeroAbilitySystemComponent == nullptr)
	{
		HeroAbilitySystemComponent = Cast<UBase_AbilitySystemComponent>(AbilitySystemComponent);
	}
	return HeroAbilitySystemComponent;

}

UBase_AttributeSet* UHeroWidgetController::GetHeroAS()
{
	if (HeroAttributeSet == nullptr)
	{
		HeroAttributeSet = Cast<UBase_AttributeSet>(AttributeSet);
	}
	return HeroAttributeSet;
}
