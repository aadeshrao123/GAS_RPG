// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Interaction/CombatInterface.h"
#include "Hero_PlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FONPlayerStatChanged, int32 /*StatChanged*/);

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GAS_RPG_API AHero_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHero_PlayerState();

	//Returns the ability system component to use for this actor.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() {return AttributeSet;}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE int32 GetPlayerLevel() const {return Level; }
	FORCEINLINE int32 GetPlayerXP() const {return XP; }
	FORCEINLINE int32 GetAttributePoints() const {return AttributePoints; }
	FORCEINLINE int32 GetSpellPoints() const {return SpellPoints; }

	void SetXP(int32 XPToSet);
	void SetLevel(int32 LevelToSet);
	void SetAttributePoints(int32 AttributePointsToSet);
	void SetSpellPoints(int32 SpellPointsToSet);

	void AddToLevel(int32 LevelToAdd);
	void AddToXP(int32 XPToAdd);
	void AddAttributePoints(int32 AttributePointsToSet);
	void AddSpellPoints(int32 SpellPointsToSet);


	FONPlayerStatChanged OnXPChangedDelegate;
	FONPlayerStatChanged OnLevelChangedDelegate;
	FONPlayerStatChanged OnAttributePointsChangedDelegate;
	FONPlayerStatChanged OnSpellPointsDelegate;



protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoints)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpellPoints)
	int32 SpellPoints = 0;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
};
