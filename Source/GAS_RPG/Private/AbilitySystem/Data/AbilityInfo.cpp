// Copyright AadeshRao


#include "AbilitySystem/Data/AbilityInfo.h"

FHeroAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FHeroAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}
	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for Ability Tag [%s] on ABilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	return FHeroAbilityInfo();
}
