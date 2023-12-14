// Copyright AadeshRao


#include "RPGAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "RPG_GameplayTags.h"

URPGAssetManager& URPGAssetManager::Get()
{
	check(GEngine);
	URPGAssetManager* AssetManager = Cast<URPGAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void URPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FRPG_GameplayTags::InitializeNativeGameplayTags();

	//This is required to use Gameplay TargetData
	UAbilitySystemGlobals::Get().InitGlobalData();
}
