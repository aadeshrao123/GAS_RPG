// Copyright AadeshRao


#include "Player/Hero_PlayerState.h"

#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "AbilitySystem/Base_AttributeSet.h"
#include "Net/UnrealNetwork.h"

AHero_PlayerState::AHero_PlayerState()
{
	NetUpdateFrequency = 100.f; //For setting the value of how often server should update 100 means server will update all clients 100 times per second

	AbilitySystemComponent = CreateDefaultSubobject<UBase_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBase_AttributeSet>("AttributeSet");

}

UAbilitySystemComponent* AHero_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AHero_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHero_PlayerState, Level);
	DOREPLIFETIME(AHero_PlayerState, XP);
	DOREPLIFETIME(AHero_PlayerState, AttributePoints);
	DOREPLIFETIME(AHero_PlayerState, SpellPoints);
	
}

void AHero_PlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AHero_PlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AHero_PlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnXPChangedDelegate.Broadcast(AttributePoints);
}

void AHero_PlayerState::OnRep_SpellPoints(int32 OldSpellPoints)
{
	OnXPChangedDelegate.Broadcast(SpellPoints);
}

void AHero_PlayerState::SetXP(int32 XPToSet)
{
	XP = XPToSet;
	OnXPChangedDelegate.Broadcast(XP);
}

void AHero_PlayerState::SetLevel(int32 LevelToSet)
{
	Level = LevelToSet;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AHero_PlayerState::SetAttributePoints(int32 AttributePointsToSet)
{
	AttributePoints = AttributePointsToSet;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AHero_PlayerState::SetSpellPoints(int32 SpellPointsToSet)
{
	SpellPoints = SpellPointsToSet;
	OnSpellPointsDelegate.Broadcast(SpellPoints);
}

void AHero_PlayerState::AddToLevel(int32 LevelToAdd)
{
	Level +=LevelToAdd;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AHero_PlayerState::AddToXP(int32 XPToAdd)
{
	XP += XPToAdd;
	OnXPChangedDelegate.Broadcast(XP);
}

void AHero_PlayerState::AddAttributePoints(int32 AttributePointsToSet)
{
	AttributePoints += AttributePointsToSet;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AHero_PlayerState::AddSpellPoints(int32 SpellPointsToSet)
{
	SpellPoints = SpellPointsToSet;
	OnSpellPointsDelegate.Broadcast(SpellPoints);
}
