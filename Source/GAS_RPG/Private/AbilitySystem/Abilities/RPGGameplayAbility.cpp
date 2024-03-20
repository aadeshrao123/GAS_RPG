// Copyright AadeshRao


#include "AbilitySystem/Abilities/RPGGameplayAbility.h"

FString URPGGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default> %s, </><Level>%s</>"), L"Default Ability Name = Lorem Ipsum, Level");
}

FString URPGGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default> Next Level, </><Level>%d</> \n <Default> Causes much more damage</>"), Level);
}

FString URPGGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default> Spell Locked Until Level: %d</>"), Level);
}
