// Copyright AadeshRao


#include "AbilitySystem/Abilities/RPGGameplayAbility.h"

#include "AbilitySystem/Base_AttributeSet.h"

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

float URPGGameplayAbility::GetManaCost(float InLevel) const
{
	float ManaCost = 0.f;
	if (const UGameplayEffect* CostEffect = GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
		{
			if (Mod.Attribute == UBase_AttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				break;
			}
		}
	}
	return ManaCost;
}

float URPGGameplayAbility::GetCoolDown(float InLevel) const
{
	float CoolDown = 0.f;
	if (const UGameplayEffect* CoolDownEffect = GetCostGameplayEffect())
	{
		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, CoolDown);
	}
	return CoolDown;
}
