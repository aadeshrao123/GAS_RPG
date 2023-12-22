// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/RPG_BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class GAS_RPG_API AEnemyCharacter : public ARPG_BaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	void HitReactChange(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterClassDefault")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterClassDefault")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	UPROPERTY(BlueprintReadOnly, Category = "Combat");
	bool bHitReacting;

	UPROPERTY(BlueprintReadOnly, Category = "Combat");
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat");
	float LifeSpan = 5.f;

	
public:
	
	AEnemyCharacter();

	//Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//Enemy Interface

	//Combat Interface
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	//Combat Interface
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
};
