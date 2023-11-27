// Copyright AadeshRao


#include "Input/RPGInputConfig.h"

const UInputAction* URPGInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FRPGInputAction& Action : AbilitySystemInputAction)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			bLogNotFound = false;
			return Action.InputAction;
		}
	}
	bLogNotFound = true;
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Ability Input Action ofr InputTag [%s], on InputConfig [%s]"),*InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
