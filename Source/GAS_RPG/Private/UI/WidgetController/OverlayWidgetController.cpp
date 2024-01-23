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

	if (UBase_AbilitySystemComponent* BaseASC = Cast<UBase_AbilitySystemComponent>(AbilitySystemComponent))
	{
		if (BaseASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(BaseASC);
		}
		else
		{
			BaseASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		BaseASC->EffectAssetTags.AddLambda(
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

void UOverlayWidgetController::OnInitializeStartupAbilities(UBase_AbilitySystemComponent* Base_AbilitySystemComponent)
{
	if (!Base_AbilitySystemComponent->bStartupAbilitiesGiven) return;
}
