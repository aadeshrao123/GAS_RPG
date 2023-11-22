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

void AHero_PlayerState::OnRep_Level(int32 OldLevel)
{
	
}

void AHero_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHero_PlayerState, Level);
}
