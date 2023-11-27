// Copyright AadeshRao


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "RPG_GameplayTags.h"
#include "AbilitySystem/Base_AttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksTODependencies()
{
	Super::BindCallbacksTODependencies();
	UBase_AttributeSet* AS = Cast<UBase_AttributeSet>(AttributeSet);

	for (auto Pair : AS->TagsToAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastInitialInfo(Pair.Key, Pair.Value());
		}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UBase_AttributeSet* AS = Cast<UBase_AttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto Pair : AS->TagsToAttribute)
	{
		BroadcastInitialInfo(Pair.Key, Pair.Value());
	}
	
}

void UAttributeMenuWidgetController::BroadcastInitialInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);

}
