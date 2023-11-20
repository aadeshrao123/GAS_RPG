// Copyright AadeshRao


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "AbilitySystem/Base_AttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBase_AttributeSet* BaseAttributeSet = CastChecked<UBase_AttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(BaseAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BaseAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(BaseAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(BaseAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksTODependencies()
{
	const UBase_AttributeSet* BaseAttributeSet = CastChecked<UBase_AttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	
	Cast<UBase_AbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
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

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
