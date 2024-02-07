// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "Character/RPG_BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class UBehaviorTree;
class ARPGAIController;
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
	virtual void PossessedBy(AController* NewController) override;

	void HitReactChange(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterClassDefault")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	UPROPERTY(BlueprintReadOnly, Category = "Combat");
	bool bHitReacting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat");
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat");
	float LifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ARPGAIController> RPGAIController;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

public:
	
	AEnemyCharacter();

	//Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//Enemy Interface

	//Combat Interface
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void Die() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() override;
	//Combat Interface
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
};
