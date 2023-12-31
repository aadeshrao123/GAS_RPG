﻿// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
 *RPG_GameplayTags
 *Singleton containing native Gameplay Tags 
 * 
 */

struct FRPG_GameplayTags
{
public:
	static const FRPG_GameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	//Primary Attributes
	FGameplayTag Attributes_Primary_Strength; // Represents the primary attribute for Strength, influencing physical power.
	FGameplayTag Attributes_Primary_Intelligence; // Represents the primary attribute for Intelligence, influencing magical power.
	FGameplayTag Attributes_Primary_Resilience; // Represents the primary attribute for Resilience, providing resistance to various forms of damage.
	FGameplayTag Attributes_Primary_Vigor; // Represents the primary attribute for Vigor, enhancing overall vitality and endurance.

	//Secondary Attributes
	FGameplayTag Attributes_Secondary_Armor; // Represents the secondary attribute for Armor, reducing the damage taken.
	FGameplayTag Attributes_Secondary_ArmorPenetration; // Represents the secondary attribute for Armor Penetration, increasing damage dealt to armored targets.
	FGameplayTag Attributes_Secondary_BlockChance; // Represents the secondary attribute for Block Chance, the chance to block incoming attacks.
	FGameplayTag Attributes_Secondary_CriticalHitChance; // Represents the secondary attribute for Critical Hit Chance, the chance to land a critical hit.
	FGameplayTag Attributes_Secondary_CriticalHitDamage; // Represents the secondary attribute for Critical Hit Damage, increasing damage on critical hits.
	FGameplayTag Attributes_Secondary_CriticalHitResistance; // Represents the secondary attribute for Critical Hit Resistance, reducing damage taken from critical hits.
	FGameplayTag Attributes_Secondary_HealthRegeneration; // Represents the secondary attribute for Health Regeneration, the rate at which health is restored over time.
	FGameplayTag Attributes_Secondary_ManaRegeneration; // Represents the secondary attribute for Mana Regeneration, the rate at which mana is restored over time.
	FGameplayTag Attributes_Secondary_MaxHealth; // Represents the vital attribute for Maximum Health, the total health pool.
	FGameplayTag Attributes_Secondary_MaxMana; // Represents the vital attribute for Maximum Mana, the total mana pool.

	//Resistances
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Physical;
	
	
	//InputTags
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_5;

	//DamageTypes
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Physical;

	FGameplayTag Abilities_Attack;

	//Sockets
	FGameplayTag Sockets_Attack_Weapon;
	FGameplayTag Sockets_Attack_RightHand;
	FGameplayTag Sockets_Attack_LeftHand;

	//Attack Montages
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;


	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	FGameplayTag HitReact;

private:
	static FRPG_GameplayTags GameplayTags;
	
};
