// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FRPGLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUPRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointRewards = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointReward = 1;
};

/**
 * 
 */
UCLASS()
class GAS_RPG_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "LevelUP")
	TArray<FRPGLevelUpInfo> LevelUpInfo;

	int32 FindLevelForXP(int32 XP);
};
