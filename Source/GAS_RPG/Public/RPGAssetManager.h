// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RPGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static URPGAssetManager& Get();

protected:
	void StartInitialLoading() override;
};
