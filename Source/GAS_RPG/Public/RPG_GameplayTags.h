// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/*
 *RPG_GameplayTags
 *Singleton containing native Gameplay Tags 
 * 
 */

struct FRPG_GameplayTags
{
public:
	static const FRPG_GameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
protected:

private:
	static FRPG_GameplayTags GameplayTags;
	
};
