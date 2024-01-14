// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "RPGDamageGamaplayAbility.h"
#include "RPGGameplayAbility.h"
#include "RPGProjectileSpell.generated.h"

class ARPGProjectile;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGProjectileSpell : public URPGDamageGamaplayAbility
{
	GENERATED_BODY()
protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ARPGProjectile> ProjectileClass;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag);

};
