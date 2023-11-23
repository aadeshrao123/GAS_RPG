// Copyright AadeshRao


#include "AbilitySystem/Data/AttributeInfo.h"

FRPGAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FRPGAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			bLogNotFound = true;
			return Info;
		}
		bLogNotFound = false;
	}
	if (!bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), * GetNameSafe(this));
	}

	return FRPGAttributeInfo();
}
