// Copyright AadeshRao


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/Base_AttributeSet.h"

void UOverlayWidgetController::BrodcastInitialValues()
{
	const UBase_AttributeSet* ASS = CastChecked<UBase_AttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(ASS->GetHealth());
	OnMaxHealthChanged.Broadcast(ASS->GetMaxHealth());
}
