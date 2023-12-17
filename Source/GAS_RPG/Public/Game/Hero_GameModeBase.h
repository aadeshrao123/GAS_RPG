// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Hero_GameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class GAS_RPG_API AHero_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
