// Copyright AadeshRao


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "RPG_GameplayTags.h"
#include "AbilitySystem/Base_AttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksTODependencies()
{
	Super::BindCallbacksTODependencies();
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UBase_AttributeSet* AS = Cast<UBase_AttributeSet>(AttributeSet);

	check(AttributeInfo);
	FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FRPG_GameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = 	AS->GetStrength();

	AttributeInfoDelegate.Broadcast(Info);

	
}
