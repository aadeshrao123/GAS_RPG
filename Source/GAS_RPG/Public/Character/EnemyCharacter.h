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
	
public:
	
	AEnemyCharacter();
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	
};
