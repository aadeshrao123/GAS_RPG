// Copyright AadeshRao


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/Base_AttributeSet.h"

void UOverlayWidgetController::BrodcastInitialValues()
{
	const UBase_AttributeSet* ASS = CastChecked<UBase_AttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(ASS->GetHealth());
	OnMaxHealthChanged.Broadcast(ASS->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksTODependencies()
{
	const UBase_AttributeSet* ASS = CastChecked<UBase_AttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ASS->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ASS->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
