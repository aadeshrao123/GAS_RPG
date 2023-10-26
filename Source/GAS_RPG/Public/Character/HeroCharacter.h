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
class GAS_RPG_API AHeroCharacter : public ARPG_BaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHeroCharacter();

	//Returns the ability system component to use for this actor. It is living PlayerState's component 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() {return AttributeSet;}

	virtual  void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "SpirngArm")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

private:
	void InitAbilityActorInfo();
};
