// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "Character/RPG_BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterClassDefault")
	int32 Level = 1;
	
public:
	
	AEnemyCharacter();

	//Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//Enemy Interface

	//Combat Interface
	virtual int32 GetPlayerLevel() override;
	//Combat Interface
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	
};
