// Copyright AadeshRao


#include "AbilitySystem/Abilities/RPGProjectileSpell.h"

#include "Kismet/KismetSystemLibrary.h"

void URPGProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UKismetSystemLibrary::PrintString(this, FString("ActivateAbility C++"), true, true, FLinearColor::Red, 3.f);
}
