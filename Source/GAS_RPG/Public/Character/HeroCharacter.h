// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "Character/RPG_BaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "HeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAttributeSet;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class GAS_RPG_API AHeroCharacter : public ARPG_BaseCharacter
{
	GENERATED_BODY()

public:
	AHeroCharacter();
	virtual  void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//Combat Interface
	virtual int32 GetPlayerLevel() override;
	//Combat Interface



protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "SpirngArm")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

private:
	virtual void InitAbilityActorInfo() override;
};
