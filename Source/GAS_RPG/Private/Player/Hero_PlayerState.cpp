// Copyright AadeshRao


#include "Player/Hero_PlayerState.h"

#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "AbilitySystem/Base_AttributeSet.h"

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
